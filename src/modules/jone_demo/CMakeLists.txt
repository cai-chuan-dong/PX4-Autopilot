
px4_add_module(
		MODULE modules__jone_demo
		MAIN jone_demo
		COMPILE_FLAGS
		SRCS
			JoneDemo.cpp
			JoneDemo.hpp
		DEPENDS
			controllib
			geo
			SlewRate
)