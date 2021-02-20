native:
	@mkdir -p build/
	@g++  modules/*.cc native-tool.cc -std=c++11 -Iincludes/ -o build/exif-tool -lpthread

web:
	@mkdir -p build/
	@g++  modules/*.cc web.cc  -std=c++11 -Iincludes/ -o webo -std=c++14 -lpthread -o build/server