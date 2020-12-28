/*
 * Copyright (c) 1999-2007 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/*
 *	Header file for Unified Buffer Cache.
 *
 */

#ifndef _SYS_UBC_H_
#define _SYS_UBC_H_

#include <sys/appleapiopts.h>
#include <sys/cdefs.h>
#include <sys/kernel_types.h>
#include <kern/locks.h>
#include <mach/machine.h>
#include <mach/memory_object_types.h>
#include <sys/ucred.h>

#ifdef KERNEL_PRIVATE
#include <sys/imgact.h>
#endif // KERNEL_PRIVATE

/* defns for ubc_msync() and ubc_msync */

#define UBC_PUSHDIRTY   0x01    /* clean any dirty pages in the specified range to the backing store */
#define UBC_PUSHALL     0x02    /* push both dirty and precious pages to the backing store */
#define UBC_INVALIDATE  0x04    /* invalidate pages in the specified range... may be used with UBC_PUSHDIRTY/ALL */
#define UBC_SYNC        0x08    /* wait for I/Os generated by UBC_PUSHDIRTY to complete */

__BEGIN_DECLS

off_t           ubc_blktooff(struct vnode *, daddr64_t);
daddr64_t       ubc_offtoblk(struct vnode *, off_t);
off_t   ubc_getsize(struct vnode *);
int     ubc_setsize(struct vnode *, off_t);

#ifdef KERNEL_PRIVATE

enum {
	UBC_SETSIZE_NO_FS_REENTRY = 1
};
typedef uint32_t ubc_setsize_opts_t;

errno_t ubc_setsize_ex(vnode_t vp, off_t nsize, ubc_setsize_opts_t opts);

#endif // KERNEL_PRIVATE

kauth_cred_t ubc_getcred(struct vnode *);
struct thread;
int     ubc_setthreadcred(struct vnode *, struct proc *, struct thread *);

errno_t ubc_msync(vnode_t, off_t, off_t, off_t *, int);
int     ubc_pages_resident(vnode_t);
int     ubc_page_op(vnode_t, off_t, int, ppnum_t *, int *);
int     ubc_range_op(vnode_t, off_t, off_t, int, int *);

#ifdef KERNEL_PRIVATE
/* This API continues to exist only until <rdar://4714366> is resolved */
int     ubc_setcred(struct vnode *, struct proc *) __deprecated;
/* code signing */
struct cs_blob;
struct cs_blob *ubc_cs_blob_get(vnode_t, cpu_type_t, off_t);

/* apis to handle generation count for cs blob */
void cs_blob_reset_cache(void);
int ubc_cs_blob_revalidate(vnode_t, struct cs_blob *, struct image_params *, int);
int ubc_cs_generation_check(vnode_t);

int cs_entitlements_blob_get(proc_t, void **, size_t *);
int cs_blob_get(proc_t, void **, size_t *);
const char *cs_identity_get(proc_t);

#endif

/* cluster IO routines */
void    cluster_update_state(vnode_t, vm_object_offset_t, vm_object_offset_t, boolean_t);

int     advisory_read(vnode_t, off_t, off_t, int);
int     advisory_read_ext(vnode_t, off_t, off_t, int, int (*)(buf_t, void *), void *, int);

int     cluster_read(vnode_t, struct uio *, off_t, int);
int     cluster_read_ext(vnode_t, struct uio *, off_t, int, int (*)(buf_t, void *), void *);

int     cluster_write(vnode_t, struct uio *, off_t, off_t, off_t, off_t, int);
int     cluster_write_ext(vnode_t, struct uio *, off_t, off_t, off_t, off_t, int, int (*)(buf_t, void *), void *);

int     cluster_pageout(vnode_t, upl_t, upl_offset_t, off_t, int, off_t, int);
int     cluster_pageout_ext(vnode_t, upl_t, upl_offset_t, off_t, int, off_t, int, int (*)(buf_t, void *), void *);

int     cluster_pagein(vnode_t, upl_t, upl_offset_t, off_t, int, off_t, int);
int     cluster_pagein_ext(vnode_t, upl_t, upl_offset_t, off_t, int, off_t, int, int (*)(buf_t, void *), void *);

int     cluster_push(vnode_t, int);
int     cluster_push_ext(vnode_t, int, int (*)(buf_t, void *), void *);
int     cluster_push_err(vnode_t, int, int (*)(buf_t, void *), void *, int *);

int     cluster_bp(buf_t);
int     cluster_bp_ext(buf_t, int (*)(buf_t, void *), void *);

void    cluster_zero(upl_t, upl_offset_t, int, buf_t);

int     cluster_copy_upl_data(uio_t, upl_t, int, int *);
int     cluster_copy_ubc_data(vnode_t, uio_t, int *, int);

typedef struct cl_direct_read_lock cl_direct_read_lock_t;
cl_direct_read_lock_t *cluster_lock_direct_read(vnode_t vp, lck_rw_type_t exclusive);
void cluster_unlock_direct_read(cl_direct_read_lock_t *lck);

/* UPL routines */
#ifndef XNU_KERNEL_PRIVATE
int     ubc_create_upl(vnode_t, off_t, int, upl_t *, upl_page_info_t **, int);
#endif /* XNU_KERNEL_PRIVATE */
int     ubc_upl_map(upl_t, vm_offset_t *);
int     ubc_upl_unmap(upl_t);
int     ubc_upl_commit(upl_t);
int     ubc_upl_commit_range(upl_t, upl_offset_t, upl_size_t, int);
int     ubc_upl_abort(upl_t, int);
int     ubc_upl_abort_range(upl_t, upl_offset_t, upl_size_t, int);
void    ubc_upl_range_needed(upl_t, int, int);

upl_page_info_t *ubc_upl_pageinfo(upl_t);
upl_size_t ubc_upl_maxbufsize(void);

int     is_file_clean(vnode_t, off_t);

errno_t mach_to_bsd_errno(kern_return_t mach_err);

#ifdef KERNEL_PRIVATE

int     ubc_create_upl_external(vnode_t, off_t, int, upl_t *, upl_page_info_t **, int);
#ifdef  XNU_KERNEL_PRIVATE
int     ubc_create_upl_kernel(vnode_t, off_t, int, upl_t *, upl_page_info_t **, int, vm_tag_t);
#endif  /* XNU_KERNEL_PRIVATE */

boolean_t ubc_is_mapped(const struct vnode *, boolean_t *writable);
__attribute__((pure)) boolean_t ubc_is_mapped_writable(const struct vnode *);

uint32_t cluster_max_io_size(mount_t, int);

#endif

__END_DECLS

#endif  /* _SYS_UBC_H_ */
