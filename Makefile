snake:
	@gcc -lpthread main.c graphics.c -o snake
	@chmod +x ./snake
	@echo
	@echo "Snake built. Run it using ./snake"


install: snake
	@cp ./snake /usr/local/bin/
	@echo
	@echo "Snake installed to /usr/local/bin/snake"
