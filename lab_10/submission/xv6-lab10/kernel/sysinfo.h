#ifndef XV6_SYSINFO_H
#define XV6_SYSINFO_H

struct sysinfo {
  uint64 freemem;  // Bytes on the physical page allocator's free list.
  uint64 nproc;    // Process table entries not in state UNUSED.
};

#endif
