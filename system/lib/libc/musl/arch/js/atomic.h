#ifndef _INTERNAL_ATOMIC_H
#define _INTERNAL_ATOMIC_H

#include <stdint.h>
#include <emscripten/threading.h>

static inline int a_ctz_l(unsigned long x)
{
	if (x == 0)
		return 32;
	int nTrailingZeros = 0;
	while(!(x&1))
	{
		++nTrailingZeros;
		x >>= 1;
	}
	return nTrailingZeros;
}

static inline int a_ctz_64(uint64_t x)
{
	uint32_t lo = (uint32_t)x;
	if (lo == 0)
		return a_ctz_l((unsigned long)(x >> 32)) + 32;
	else
		return a_ctz_l((unsigned long)lo);
}

static inline void a_and_64(volatile uint64_t *p, uint64_t v)
{
	*p &= v;
}

static inline void a_or_64(volatile uint64_t *p, uint64_t v)
{
	*p |= v;
}

static inline void a_store_l(volatile void *p, long x)
{
	emscripten_atomic_store_u32((void*)p, x);
}

static inline void a_or_l(volatile void *p, long v)
{
	emscripten_atomic_or_u32((void*)p, v);
}

static inline void *a_cas_p(volatile void *p, void *t, void *s)
{
	return (void*)emscripten_atomic_cas_u32(p, (uint32_t)t, (uint32_t)s);
}

static inline long a_cas_l(volatile void *p, long t, long s)
{
	return emscripten_atomic_cas_u32(p, t, s);
}

static inline int a_cas(volatile int *p, int t, int s)
{
	return emscripten_atomic_cas_u32(p, t, s);
}

static inline void a_or(volatile void *p, int v)
{
	emscripten_atomic_or_u32((void*)p, v);
}

static inline void a_and(volatile void *p, int v)
{
	emscripten_atomic_and_u32((void*)p, v);
}

static inline void a_inc(volatile int *x)
{
	emscripten_atomic_add_u32((void*)x, 1);
}

static inline void a_dec(volatile int *x)
{
	emscripten_atomic_sub_u32((void*)x, 1);
}

static inline void a_store(volatile int *p, int x)
{
	emscripten_atomic_store_u32((void*)p, x);
}

static inline void a_spin()
{
}

static inline void a_crash()
{
}


#endif
