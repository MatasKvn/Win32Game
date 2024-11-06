
run:
	cmake -S . -B build -G "MinGW Makefiles"
	make -C build
	build/main.exe

clean:
	rm -rf build