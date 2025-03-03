        .seg    "text"
#if !defined(AO_NO_SPARC_V9)
        .globl  AO_fetch_compare_and_swap_full
AO_fetch_compare_and_swap_full:
        membar  #StoreLoad | #LoadLoad
#if defined(__arch64__) || defined(__sparcv9)
        casx    [%o0],%o1,%o2
#else
        cas     [%o0],%o1,%o2
#endif
        membar  #StoreLoad | #StoreStore
        retl
        mov     %o2, %o0
#endif
        .globl  AO_test_and_set_full
AO_test_and_set_full:
        retl
        ldstub  [%o0],%o0
