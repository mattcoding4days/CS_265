RELEASE=$(CXX) $(WARNINGS) $(OUT_FLG)
DEBUG=$(CXX) $(WARNINGS) $(DEBUG_FLG) $(OUT_FLG)
CXX=g++
DEBUG_FLG=-g
BUILD_FLG=-c
OUT_FLG=-o
WARNINGS=-Wall -Wextra 
TARGET=bin/grader
TARGET_DEBUG=bin/graderdebug
OBJ_DIR=obj/
OBJ_DEBUG_DIR=objd/
OBJFILES=$(OBJ_DIR)*.o
OBJFILESDEBUG=$(OBJ_DEBUG_DIR)*.o
VERSION=2.0


.PHONY: all clean

all: $(TARGET) $(TARGET_DEBUG)

$(TARGET): obj/grader.o obj/argparser.o obj/utillity.o obj/evaluation.o obj/student.o obj/grader.o
	$(RELEASE) bin/grader $(OBJFILES)

$(TARGET_DEBUG): objd/grader.o objd/argparser.o objd/utillity.o objd/evaluation.o objd/student.o objd/grader.o
	$(DEBUG) bin/graderdebug $(OBJFILESDEBUG)



# Release
obj/grader.o: src/grader.cc
	@echo
	@echo "Building Grader Release Version: $(VERSION)"
	@echo "===================================="
	$(CXX) $(WARNINGS) $(BUILD_FLG) $< $(OUT_FLG) $@

obj/argparser.o: src/argparser.cc
	$(CXX) $(WARNINGS) $(BUILD_FLG) $< $(OUT_FLG) $@

obj/utillity.o: src/utillity.cc
	$(CXX) $(WARNINGS) $(BUILD_FLG) $< $(OUT_FLG) $@

obj/evaluation.o: src/evaluation.cc
	$(CXX) $(WARNINGS) $(BUILD_FLG) $< $(OUT_FLG) $@

obj/student.o: src/student.cc
	$(CXX) $(WARNINGS) $(BUILD_FLG) $< $(OUT_FLG) $@



# Debug
objd/grader.o: src/grader.cc
	@echo
	@echo "Building Grader Debug Version: $(VERSION)"
	@echo "=================================="
	$(CXX) $(WARNINGS) $(BUILD_FLG) $(DEBUG_FLG) $< $(OUT_FLG) $@

objd/argparser.o: src/argparser.cc
	$(CXX) $(WARNINGS) $(BUILD_FLG) $(DEBUG_FLG) $< $(OUT_FLG) $@

objd/utillity.o: src/utillity.cc
	$(CXX) $(WARNINGS) $(BUILD_FLG) $(DEBUG_FLG) $< $(OUT_FLG) $@

objd/evaluation.o: src/evaluation.cc
	$(CXX) $(WARNINGS) $(BUILD_FLG) $(DEBUG_FLG) $< $(OUT_FLG) $@

objd/student.o: src/student.cc
	$(CXX) $(WARNINGS) $(BUILD_FLG) $(DEBUG_FLG) $< $(OUT_FLG) $@


clean:
	@rm $(OBJFILES)
	@rm $(OBJFILESDEBUG)
	@rm $(TARGET)
	@rm $(TARGET_DEBUG)
	@echo cleaned....
