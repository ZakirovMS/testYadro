all:
	g++ -o result factoryModeling/main.cpp factoryModeling/machine.cpp factoryModeling/factory.cpp \
	factoryModeling/product.cpp factoryModeling/auxil/checkers.cpp factoryModeling/auxil/outStructs.cpp \
	-I factoryModeling -I factoryModeling/auxil

run: result
	@if [ -z "$(path)" ]; \
	then echo "Path required"; \
	exit 1; \
	fi
	./result $(path)

run-def: result
	./result factoryModeling/src/data.txt   # если data.txt лежит относительно текущей папки (там, где Makefile)

run-folder: result
	@if [ -z "$(folder)" ]; then \
		echo "Folder required."; \
		exit 1; \
	fi
	@if [ ! -d "$(folder)" ]; then \
		echo "Folder '$(folder)' does not exist"; \
		exit 1; \
	fi
	@find "$(folder)" -maxdepth 1 -type f -print | while IFS= read -r file; do \
		./result "$$file"; \
		echo; \
	done

clean:
	rm -f result