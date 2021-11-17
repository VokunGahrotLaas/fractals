
#define f_always_inline __attribute__((always_inline))
#define f_const __attribute__((const))
#define f_constructor __attribute__((constructor))
#define f_destructor __attribute__((destructor))
#define f_deprecated __attribute__((deprecated))
#define f_deprecated_msg(msg) __attribute__((deprecated(msg)))
#define f_format(archtype, string_index, first_to_check)                       \
	__attribute__((format((archetype), (string_index), (first_to_check))))
#define f_format_printf(string_index, first_to_check)                          \
	__attribute__((format(printf, (string_index), (first_to_check))))
#define f_format_scanf(string_index, first_to_check)                           \
	__attribute__((format(scanf, (string_index), (first_to_check))))
#define f_malloc __attribute__((malloc))
#define f_noinline __attribute__((noinline))
#define f_nonnull __attribute__((nonnull))
#define f_noreturn __attribute__((noreturn))
#define f_pure __attribute__((pure))
#define f_neturns_nonnull __attribute__((returns_nonnull))
#define f_unused __attribute__((unused))
#define f_warn_unused_result __attribute__((warn_unused_result))
#define f_vector_size(sz) __attribute__((vector_size(sz)))

#define f_force_inline always_inline inline

#ifdef DEBUG_FRACTALS
#define f_debug(...)                                                           \
	do {                                                                       \
		printf(__VA_ARGS__);                                                   \
		putc('\n', stdout);                                                    \
	} while (false);
#define f_debug_func(...)                                                      \
	do {                                                                       \
		printf("%s: ", __PRETTY_FUNCTION__);                                   \
		f_debug(__VA_ARGS__);                                                  \
	} while (false);
#define f_debug_func_name() printf("%s\n", __PRETTY_FUNCTION__);
#else						// DEBUG_FRACTALS
#define f_debug(...)		/**/
#define f_debug_func(...)	/**/
#define f_debug_func_name() /**/
#endif						// DEBUG_FRACTALS

#define f_rand_color()                                                         \
	(SDL_Color({ (Uint8)rand(), (Uint8)rand(), (Uint8)rand(), 255 }))
