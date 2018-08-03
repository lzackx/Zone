//
//  ViewController.m
//  Source1_PortBased
//
//  Created by lzackx on 2018/3/20.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import "ViewController.h"
#import <mach/mach.h>

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    /*
     在iOS中，尤其是较新的系统版本中，Foundation封装的Port Based input source（即Source1）
     的API使用限制非常多，步步是坑，一切需以实际情况为准。
     */
    [self runFoundationSource1];
    [self runCoreFoundationSource1];
}

- (void)createCoreFoundationLocalPortWithPortName:(CFStringRef *)portName {
    
    // Create a local port for receiving responses.
    /*
     struct __CFMessagePort {
         CFRuntimeBase _base;
         CFLock_t _lock;
         CFStringRef _name;
         CFMachPortRef _port;        // immutable; invalidated
         CFMutableDictionaryRef _replies;
         int32_t _convCounter;
         int32_t _perPID;            // zero if not per-pid, else pid
         CFMachPortRef _replyPort;        // only used by remote port; immutable once created; invalidated
         CFRunLoopSourceRef _source;        // only used by local port; immutable once created; invalidated
         dispatch_source_t _dispatchSource;  // only used by local port; invalidated
         dispatch_queue_t _dispatchQ;    // only used by local port
         CFMessagePortInvalidationCallBack _icallout;
         CFMessagePortCallBack _callout;    // only used by local port; immutable
         CFMessagePortCallBackEx _calloutEx;    // only used by local port; immutable
         CFMessagePortContext _context;    // not part of remote port; immutable; invalidated
     };
     */
    CFMessagePortRef messagePort;
    /*
     struct __CFRunLoopSource {
         CFRuntimeBase _base;
         uint32_t _bits;
         pthread_mutex_t _lock;
         CFIndex _order;            // immutable
         CFMutableBagRef _runLoops;
         union {
             CFRunLoopSourceContext version0;    // immutable, except invalidation
             CFRunLoopSourceContext1 version1;    // immutable, except invalidation
         } _context;
     };
     */
    CFRunLoopSourceRef source1;
    /*
     typedef struct {
         CFIndex    version;
         void *    info;
         const void *(*retain)(const void *info);
         void    (*release)(const void *info);
         CFStringRef    (*copyDescription)(const void *info);
     } CFMessagePortContext;
     */
    CFMessagePortContext context = {0, (__bridge void *)(self), NULL, NULL, NULL};
    Boolean shouldFreeInfo;
    // Create a string with the port name.
    // Create the port.
    messagePort = CFMessagePortCreateLocal(NULL,
                                           *portName,
                                           &coreFoundationSourceHandler,
                                           &context,
                                           &shouldFreeInfo);
    
    if (messagePort != NULL) {
        // The port was successfully created.
        // Now create a run loop source for it.
        source1 = CFMessagePortCreateRunLoopSource(NULL, messagePort, 0);
        if (source1) {
            // Add the source to the current run loop.
            CFRunLoopAddSource(CFRunLoopGetCurrent(), source1, kCFRunLoopDefaultMode);
            // Once installed, these can be freed.
            CFRelease(messagePort);
        }
    }
}

CFDataRef coreFoundationSourceHandler(CFMessagePortRef local,
                                      SInt32 msgid,
                                      CFDataRef data,
                                      void* info) {
    NSLog(@"%i", msgid);
    CFMessagePortRef messagePort;
    CFStringRef portName;
    CFIndex bufferLength = CFDataGetLength(data);
    UInt8* buffer = CFAllocatorAllocate(NULL, bufferLength, 0);
    CFDataGetBytes(data, CFRangeMake(0, bufferLength), buffer);
    portName = CFStringCreateWithBytes (NULL, buffer, bufferLength, kCFStringEncodingASCII, FALSE);
    // You must obtain a remote message port by name.
    messagePort = CFMessagePortCreateRemote(NULL, (CFStringRef)portName);
    
    NSLog(@"portName: %@, data: %@, info: %@", portName, [[NSString alloc] initWithData:(__bridge NSData *)data encoding:NSUTF8StringEncoding], info);
    
    // Clean up.
    CFRelease(portName);
    CFAllocatorDeallocate(NULL, buffer);
    return NULL;
}

- (void)createCoreFoundationRemotePort {
    
    // Create the remote port
    CFMessagePortRef clientPort;
    CFStringRef clientPortName = CFStringCreateWithFormat(NULL, NULL, CFSTR("com.lzackx.port.client"));
    clientPort = CFMessagePortCreateRemote(NULL, clientPortName);
    // Free the string that was passed in param.
    CFRelease(clientPortName);
    
    // Create a local port
    CFStringRef severPortName = CFStringCreateWithFormat(NULL, NULL, CFSTR("com.lzackx.port.server"));
    // Store the port in this thread’s context info for later reference.
    CFMessagePortContext context = {0, clientPort, NULL, NULL, NULL};
    Boolean shouldFreeInfo;
    CFMessagePortRef serverPort = CFMessagePortCreateLocal(NULL,
                                                       severPortName,
                                                       &coreFoundationSourceHandler,
                                                       &context,
                                                       &shouldFreeInfo);
    if (shouldFreeInfo) {
        // Couldn't create a server port, so kill the thread.
        return;
    }
    CFRunLoopSourceRef source1 = CFMessagePortCreateRunLoopSource(NULL, serverPort, 0);
    if (!source1) {
        // Couldn't create a local port, so kill the thread.
        return;
    }
    // Add the source to the current run loop.
    CFRunLoopAddSource(CFRunLoopGetCurrent(), source1, kCFRunLoopDefaultMode);
    // Once installed, these can be freed.
    CFRelease(serverPort);
    CFRelease(source1);
}

- (void)sendCoreFoundationMessageFromClientPortName:(CFStringRef *)clientPortName {
    
    // Package up the port name and send the message.
    CFDataRef returnData = NULL;
    CFDataRef outData;
    CFMessagePortRef clientPort;
    clientPort = CFMessagePortCreateRemote(NULL, *clientPortName);
    if (!clientPort) {
        return;
    }
    CFIndex stringLength = CFStringGetLength(*clientPortName);
    UInt8* buffer = CFAllocatorAllocate(NULL, stringLength, 0);
    
    CFStringGetBytes(*clientPortName,
                     CFRangeMake(0,stringLength),
                     kCFStringEncodingASCII,
                     0,
                     FALSE,
                     buffer,
                     stringLength,
                     NULL);
    
    
    outData = CFDataCreate(NULL, buffer, stringLength);
    CFMessagePortSendRequest(clientPort,
                             1,
                             outData,
                             0.1,
                             0.0,
                             kCFRunLoopDefaultMode,
                             &returnData);
    
    // Clean up thread data structures.
    CFRelease(outData);
    CFAllocatorDeallocate(NULL, buffer);
    
    // Enter the run loop.
//    CFRunLoopRun();
    
}

// MARK: Core Foundation
- (void)runCoreFoundationSource1 {
    
    CFStringRef clientPortName = CFStringCreateWithFormat(NULL, NULL, CFSTR("com.lzackx.port.client"));
//    [self createCoreFoundationLocalPortWithPortName:&clientPortName];
//    [self createCoreFoundationRemotePort];
    [self sendCoreFoundationMessageFromClientPortName:&clientPortName];
    CFRelease(clientPortName);
}

// MARK: Foundation
/* delegate
 handlePortMessage:来自于NSPortDelegate，这是个很奇怪的API，参数是(NSPortMessage *)类型，
 支持iOS 2.0+、macOS 10.0+、tvOS 9.0+、watchOS 2.0+，但是(NSPortMessage *)却只支持macOS 10.0+，
 所以iOS中想要获得message的内部信息只能通过KVC。
 This is the delegate method that subclasses should send to their delegates,
 unless the subclass has something more specific that it wants to try to send first
 
 handleMachMessage:来自于NSMachPortDelegate，参数是(void *)类型，
 文档说明是以(msg_header_t)结构体类型开始的数据，使用时先通过类型转换，获得结构体的数据。
 Delegates are sent this if they respond, otherwise they are sent handlePortMessage:;
 argument is the raw Mach message
 经过推测与试验，因为并不清楚参数的数据结构，所以暂时还没找到从参数获得component内数据的方法。
 或许什么时候看看Mach中相关的源码可以清楚点。
 
 在NSPort的调用过程中假如需要设置delegate，那么只需要设置其中一个，若不设置，NSPort可以自己处理。
 */
- (void)handleMachMessage:(void *)msg {
    
    NSLog(@"self: %@, func: %s", self, __func__);
    /*
     typedef    struct
     {
         mach_msg_bits_t    msgh_bits;
         mach_msg_size_t    msgh_size;
         mach_port_t        msgh_remote_port;
         mach_port_t        msgh_local_port;
         mach_port_name_t    msgh_voucher_port;
         mach_msg_id_t        msgh_id;
     } mach_msg_header_t;
     
     typedef struct
     {
        mach_msg_size_t msgh_descriptor_count;
     } mach_msg_body_t;
     
     typedef struct
     {
         mach_msg_header_t       header;
         mach_msg_body_t         body;
     } mach_msg_base_t;

     */
    mach_msg_base_t *mach_msg_base = msg;
    NSLog(@"bits: %u ", mach_msg_base->header.msgh_bits);
    NSLog(@"id: %d ", mach_msg_base->header.msgh_id);
    NSLog(@"local port: %u ", mach_msg_base->header.msgh_local_port);
    NSLog(@"remote port: %u ", mach_msg_base->header.msgh_remote_port);
    NSLog(@"size: %u ", mach_msg_base->header.msgh_size);
    NSLog(@"voucher port: %u ", mach_msg_base->header.msgh_voucher_port);
    NSLog(@"descriptor count: %u", mach_msg_base->body.msgh_descriptor_count);
    
}

// Port
- (NSPort *)createPort {
    
    /* NSMessagePort
     Important
     Avoid NSMessagePort.
     There's little reason to use NSMessagePort rather than NSMachPort or NSSocketPort.
     There's no particular performance or functionality advantage.
     It is recommended avoiding its use.
     NSMessagePort may be deprecated in the macOS 10.6 or later.
     上述表示NSMessagePort没什么特别的处理，并且可能会被废弃，所以尽量别用
     
     NSPort *port = [NSMessagePort port];
     */
    
    /* NSSocketPort macOS 10.0+
     NSSocketPort在文档中只写着支持macOS 10.0+，iOS中没有提供API，
     但估计可以通过KVC来使用，由于不是推荐的调用方式，所以这里没有归纳，
     不过就算能用，也应算是私有API，如果用了，系统版本不同不知道会不会有影响，并且给不给过审核也不知道了。
     
     NSPort *port = [NSSocketPort port];
     */
    
    // NSMachPort
    NSPort *port = [NSMachPort port];
    
    port.delegate = self;
    return port;
}

- (void)runFoundationSource1 {
    
    NSRunLoop *currentRunLoop = [NSRunLoop currentRunLoop];
    
    NSPort *port0 = [self createPort];
    NSPort *port1 = [self createPort];
    
    // 不同的方式，需要注意当前线程中的RunLoop运行状态
    [port0 scheduleInRunLoop:currentRunLoop forMode:NSRunLoopCommonModes];
    [currentRunLoop addPort:port1 forMode:NSRunLoopCommonModes];
    
    /* API中提及了这段话
     The components array consists of a series of instances
     of some subclass of NSData, and instances of some
     subclass of NSPort; since one subclass of NSPort does
     not necessarily know how to transport an instance of
     another subclass of NSPort (or could do it even if it
     knew about the other subclass), all of the instances
     of NSPort in the components array and the 'receivePort'
     argument MUST be of the same subclass of NSPort that
     receives this message.  If multiple DO transports are
     being used in the same program, this requires some care.
     
     因为（sendBeforeDate:msgid:components:from:reserved:）的components参数是（NSMutableArray*）类型，
     但是此类型只能添加NSObject或NSPort，想要此方法正常传递components参数，注意类型转换。
     */
    NSMutableArray *components0 = [NSMutableArray arrayWithObjects:port0, [@"data0" dataUsingEncoding:NSUTF8StringEncoding], nil];
    NSMutableArray *components1 = [NSMutableArray arrayWithObject:[NSKeyedArchiver archivedDataWithRootObject:@[@"port1", @"data1"]]];
    
    NSLog(@"%p, %p", &components0, &components1);
    
    [port0 sendBeforeDate:[NSDate distantFuture] msgid:0 components:components0 from:port1 reserved:0];
    [port1 sendBeforeDate:[NSDate distantFuture] msgid:1 components:components1 from:port0 reserved:0];
}

@end










