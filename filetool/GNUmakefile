
# -*- Mode: Makefile -*- 

### This makefile produces an executable for each 
### name in the `ebase' variable

ebase :=  nctoamr amrtotxt amrtoplot flatten extract merge addbox amrtocf stats glfaces faces rescale sum pythonf diagnostics stats_luo zhenbo_stats stats_all18 stats_noghost
src_dirs = src
all:  clean libbike 

.NOTPARALLEL: all

include ../mk/Make.defs
 

#if NETCDF_INC was not defined, try to work it out from nc-config or NETCDF_HOME
ifeq ($(NETCDF_INC),)

#no NETCDF_HOME? try nc-config
ifeq ($(NETCDF_HOME), )
NETCDF_HOME = $(shell nc-config --prefix)

ifneq ($(NETCDF_HOME), )
NETCDF_INC = -I$(shell nc-config --includedir)

ifeq ($(shell nc-config --has-f90), yes)
NETCDF_LIBS = $(shell nc-config --flibs) #does no harm to link the fortran libs if present
else ifeq ($(shell nc-config --has-fortran), yes)
NETCDF_LIBS = $(shell nc-config --flibs) #does no harm to link the fortran libs if present
else
NETCDF_LIBS = $(shell nc-config --libs)
endif

endif

else
NETCDF_INC=-I$(NETCDF_HOME)/include
NETCDF_LIBS := -L$(NETCDF_HOME)/lib $(NETCDF_LIBS)
endif
endif
NETCDF_LIBS := -L /home/luo/ZFP/zfp/lib/ -lzfp -L /home/luo/ZFP/SZ/lib -lSZ  -lzstd -lzlib $(NETCDF_LIBS)
NETCDF_INC :=-I/home/luo/ZFP/zfp/include -I/home/luo/ZFP/SZ/include $(NETCDF_INC)

libbike:
	cd ../lib; $(MAKE) lib

$(info NetCDF: $(NETCDF_INC) $(NETCDF_LIBS) )
ifneq ($(NETCDF_INC), )
CPPFLAGS += -DHAVE_NETCDF $(NETCDF_INC)

endif
LIBFLAGS := -L../lib/ -lBisicles$(config) $(NETCDF_LIBS)  $(LIBFLAGS)
