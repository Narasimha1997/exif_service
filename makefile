native:
	@mkdir -p build/
	@g++  modules/*.cc native-tool.cc  -Iincludes/ -o build/exif-tool -std=c++14 -lpthread

web:
	@mkdir -p build/
	@g++  modules/*.cc web.cc  -Iincludes/ -o webo -std=c++14 -lpthread -o build/server