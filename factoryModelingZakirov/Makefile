all:
	g++ -o result main.cpp machine.cpp factory.cpp product.cpp auxil/auxiliary.cpp auxil/outStructs.cpp

run: result
	@if [ -z "$(path)" ]; \
	then echo "Path required"; \
	exit 1; \
	fi
	./result $(path)
run-def: result
	./result src/data.txt

clean:
	rm -f result
