RELEASE=$(CXX) $(WARNINGS) $(OUT_FLG)
DEBUG=$(CXX) $(WARNINGS) $(DEBUG_FLG) $(OUT_FLG)
CXX=g++
DEBUG_FLG=-g
BUILD_FLG=-c
OUT_FLG=-o
WARNINGS=-Wall -Wextra 
TARGET=bin/grader
TARGET_DEBUG=bin/graderdebug
OBJFILES=obj/*.o
OBJFILESDEBUG=objd/*.o
VERSION=2.0


.PHONY: all clean

all: $(TARGET) $(TARGET_DEBUG)

$(TARGET): obj/main.o obj/base.o obj/student.o obj/grader.o
	 $(RELEASE) bin/grader $(OBJFILES) 

$(TARGET_DEBUG): objd/main.o objd/base.o objd/student.o objd/grader.o 
	$(DEBUG) bin/graderdebug $(OBJFILESDEBUG) 

# Release
obj/main.o: src/main.cpp hdr/base.h hdr/student.h hdr/grader.h
	@echo "\nBuilding Grader Release Version: $(VERSION)"
	@echo "===================================="
	$(CXX) $(WARNINGS) $(BUILD_FLG) $< $(OUT_FLG) $@

obj/base.o: src/base.cpp hdr/base.h
	$(CXX) $(WARNINGS) $(BUILD_FLG) $< $(OUT_FLG) $@

obj/student.o: src/student.cpp hdr/student.h
	$(CXX) $(WARNINGS) $(BUILD_FLG) $< $(OUT_FLG) $@

obj/grader.o: src/grader.cpp hdr/grader.h
	$(CXX) $(WARNINGS) $(BUILD_FLG) $< $(OUT_FLG) $@

# Debug 
objd/main.o: src/main.cpp hdr/base.h hdr/student.h hdr/grader.h
	@echo "\nBuilding Grader Debug Version: $(VERSION)"
	@echo "=================================="
	$(CXX) $(WARNINGS) $(BUILD_FLG) $(DEBUG_FLG) $< $(OUT_FLG) $@

objd/base.o: src/base.cpp hdr/base.h
	$(CXX) $(WARNINGS) $(BUILD_FLG) $(DEBUG_FLG) $< $(OUT_FLG) $@

objd/student.o: src/student.cpp hdr/student.h
	$(CXX) $(WARNINGS) $(BUILD_FLG) $(DEBUG_FLG) $< $(OUT_FLG) $@

objd/grader.o: src/grader.cpp hdr/grader.h
	$(CXX) $(WARNINGS) $(BUILD_FLG) $(DEBUG_FLG) $< $(OUT_FLG) $@

clean:
	rm $(OBJFILES)
	rm $(OBJFILESDEBUG)
	rm $(TARGET)
	rm $(TARGET_DEBUG)
