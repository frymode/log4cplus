noinst_PROGRAMS += customloglevel_test

customloglevel_test_sources = \
	%D%/main.cxx \
	%D%/func.cxx \
	%D%/customloglevel.cxx

customloglevel_test_SOURCES = $(customloglevel_test_sources)

customloglevel_test_LDADD = $(liblog4cplus_la_file)

if BUILD_WITH_WCHAR_T_SUPPORT
noinst_PROGRAMS += customloglevel_testU
customloglevel_testU_CPPFLAGS = $(AM_CPPFLAGS) -DUNICODE=1
customloglevel_testU_SOURCES = $(customloglevel_test_sources)
customloglevel_testU_LDADD = $(liblog4cplusU_la_file)
endif
