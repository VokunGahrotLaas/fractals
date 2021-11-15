
#define always_inline __attribute__((always_inline))
#define const __attribute__((const))
#define constructor __attribute__((constructor))
#define destructor __attribute__((destructor))
#define deprecated __attribute__((deprecated))
#define deprecated_msg(msg) __attribute__((deprecated(msg)))
#define format(archtype, string_index, first_to_check)                         \
	__attribute__((format((archetype), (string_index), (first_to_check))))
#define format_printf(string_index, first_to_check)                            \
	__attribute__((format(printf, (string_index), (first_to_check))))
#define format_scanf(string_index, first_to_check)                             \
	__attribute__((format(scanf, (string_index), (first_to_check))))
#define malloc __attribute__((malloc))
#define noinline __attribute__((noinline))
#define nonnull __attribute__((nonnull))
#define noreturn __attribute__((noreturn))
#define pure __attribute__((pure))
#define neturns_nonnull __attribute__((returns_nonnull))
#define unused __attribute__((unused))
#define warn_unused_result __attribute__((warn_unused_result))
#define vector_size(sz) __attribute__((vector_size(sz)))

#define force_inline always_inline inline

#ifdef DEBUG_FRACTALS
#define debug(...) do { printf(__VA_ARGS__); } while (false);
#else // DEBUG_FRACTALS
#define debug(...) /* NOTHING */
#endif // DEBUG_FRACTALS
