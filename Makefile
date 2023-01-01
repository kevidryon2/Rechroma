all:
	make tools
	make launcher
	make install
	make run

maker:
	make tools
	make install
	~/.rechroma/maker

launcher:
	make rechroma_debug
	#tools/makedropperfiles
	bash raybuild.sh launcher

rechroma_debug:
	echo "Making Rechroma..."
	bash raybuild.sh rechroma
	echo "Done!"

rechroma_release:
	make rechroma_debug

clean:
	rm build/*.*
	touch build/rechroma
	
tools:
	#gcc makedropper.c -o tools/makedropperfiles
	bash raybuild.sh levelmaker
	cp build/levelmaker tools
	
	
install:
	echo "mkdir ~/.rechroma; return 0" | sh #If directory already exists (it returns 1), it will stop make (so i made sure it always returned 0)
	cp build/rechroma ~/.rechroma/
	cp build/launcher ~/.rechroma/
	cp build/levelmaker ~/.rechroma/maker
	cp crash.mp3 ~/.rechroma/
	cp data.rrf ~/.rechroma/
run:
	~/.rechroma/launcher
