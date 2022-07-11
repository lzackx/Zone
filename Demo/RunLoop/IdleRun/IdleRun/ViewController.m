//
//  ViewController.m
//  IdleRun
//
//  Created by lzackx on 2018/3/20.
//  Copyright © 2018年 lzackx. All rights reserved.
//

#import "ViewController.h"

typedef void(^TaskBlock)(void);

@interface ViewController () <UICollectionViewDataSource, UICollectionViewDelegate>

@property (nonatomic, strong) UICollectionView *collectionView;
@property (nonatomic, strong) NSMutableDictionary *tasks;
@property (nonatomic, strong) NSTimer *timer;

@end

@implementation ViewController

- (void)loadView {
    UICollectionViewFlowLayout *collectionViewLayout = [[UICollectionViewFlowLayout alloc] init];
    collectionViewLayout.itemSize = CGSizeMake(UIScreen.mainScreen.bounds.size.width / 8 - 2, UIScreen.mainScreen.bounds.size.width / 8 - 2);
    collectionViewLayout.minimumLineSpacing = 1;
    collectionViewLayout.minimumInteritemSpacing = 1;
    self.collectionView = [[UICollectionView alloc] initWithFrame:UIScreen.mainScreen.bounds collectionViewLayout:collectionViewLayout];
    self.collectionView.backgroundColor = UIColor.whiteColor;
    self.collectionView.dataSource = self;
    self.collectionView.delegate = self;
    self.view = self.collectionView;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self.collectionView registerClass:[UICollectionViewCell class] forCellWithReuseIdentifier:@"CollectionViewCell"];
    
    [self runRunLoopObserver];
}

// MARK: Run Loop Observer
- (void)runRunLoopObserver {
    
    // The application uses garbage collection, so no autorelease pool is needed.
    // Create a run loop observer and attach it to the run loop.
    /*
     typedef struct {
     CFIndex    version;
     void *    info;
     const void *(*retain)(const void *info);
     void    (*release)(const void *info);
     CFStringRef    (*copyDescription)(const void *info);
     } CFRunLoopObserverContext;
     */
    CFRunLoopObserverContext context = {
        0,
        (__bridge void *)(self),
        &CFRetain,
        &CFRelease,
        NULL
    };
    CFRunLoopObserverRef observer = CFRunLoopObserverCreate(kCFAllocatorDefault,
                                                            kCFRunLoopBeforeWaiting,
                                                            YES,
                                                            0,
                                                            &observerCallBack,
                                                            &context);
    if (observer) {
        self.tasks = [NSMutableDictionary dictionary];
        self.timer = [NSTimer scheduledTimerWithTimeInterval:0.001 repeats:YES block:^(NSTimer * _Nonnull timer) {
            // Do Nothing but to tigger observer
        }];
        CFRunLoopRef cfLoop = CFRunLoopGetCurrent();
        CFRunLoopAddObserver(cfLoop, observer, kCFRunLoopDefaultMode);
        CFRelease(observer);
    }
}

void observerCallBack(CFRunLoopObserverRef observer, CFRunLoopActivity activity, void *info) {
    
    NSLog(@"%s", __func__);
    ViewController *vc = (__bridge ViewController *)info;
    for (NSString *key in vc.tasks.allKeys) {
        NSLog(@"key: %@", key);
        ((TaskBlock)vc.tasks[key])();
        [vc.tasks removeObjectForKey:key];
        break;
    }
    
}

- (void)addTask:(TaskBlock)taskblock forKey:(NSString *)key {
    
    [self.tasks setObject:taskblock forKey:key];
}

// MARK: UICollectionView Data Source
- (nonnull __kindof UICollectionViewCell *)collectionView:(nonnull UICollectionView *)collectionView cellForItemAtIndexPath:(nonnull NSIndexPath *)indexPath {
    
    UICollectionViewCell *cell = [self.collectionView dequeueReusableCellWithReuseIdentifier:@"CollectionViewCell" forIndexPath:indexPath];
    cell.backgroundColor = UIColor.lightGrayColor;
    
    [self addTask:^{
        UIImageView *imageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"image"]];
        imageView.frame = CGRectMake(0, 0, cell.contentView.bounds.size.width / 2, cell.contentView.bounds.size.height / 2);
        [cell.contentView addSubview:imageView];
    } forKey:[NSString stringWithFormat: @"%ld.1", (long)indexPath.item]];
    
    [self addTask:^{
        UIImageView *imageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"image"]];
        imageView.frame = CGRectMake(cell.contentView.bounds.size.width / 2, 0, cell.contentView.bounds.size.width / 2, cell.contentView.bounds.size.height / 2);
        [cell.contentView addSubview:imageView];
    } forKey:[NSString stringWithFormat: @"%ld.2", (long)indexPath.item]];
    
    [self addTask:^{
        UIImageView *imageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"image"]];
        imageView.frame = CGRectMake(0, cell.contentView.bounds.size.height / 2, cell.contentView.bounds.size.width / 2, cell.contentView.bounds.size.height / 2);
        [cell.contentView addSubview:imageView];
    } forKey:[NSString stringWithFormat: @"%ld.3", (long)indexPath.item]];

    [self addTask:^{
        UIImageView *imageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"image"]];
        imageView.frame = CGRectMake(cell.contentView.bounds.size.width / 2, cell.contentView.bounds.size.height / 2, cell.contentView.bounds.size.width / 2, cell.contentView.bounds.size.height / 2);
        [cell.contentView addSubview:imageView];
    } forKey:[NSString stringWithFormat: @"%ld.4", (long)indexPath.item]];
    
    return cell;
}

- (NSInteger)collectionView:(nonnull UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    
    return 1280;
}

@end










