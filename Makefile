all:
	make tools
	make launcher
	make install
	make run

launcher:
	make rechroma_debug
	make maker
	#tools/makedropperfiles
	bash raybuild.sh launcher

rechroma_debug:
	echo "Making Rechroma..."
	bash raybuild.sh rechroma
	echo "Done!"


clean:
	rm build/*.*
	touch build/rechroma

release:
	rm build/release.tar
	make tools
	make launcher
	make install
	cp *.ogg build
	cp data.rrf build
	cd build
	tar -cf build/release.tar build/*

tools:
	#gcc makedropper.c -o tools/makedropperfiles

maker:
	bash raybuild.sh levelmaker
	cp build/levelmaker tools
	
install:
	echo "mkdir ~/.rechroma; return 0" | sh #If directory already exists (it returns 1), it will stop make (so i made sure it always returned 0)
	cp build/rechroma ~/.rechroma/
	cp build/launcher ~/.rechroma/
	cp build/levelmaker ~/.rechroma/maker
	cp *.wav ~/.rechroma/assets/
	cp data.rrf ~/.rechroma/assets/
run:
	~/.rechroma/launcher
