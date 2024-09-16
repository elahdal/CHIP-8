.PHONY: clean All

All:
	@echo "----------Building project:[ Projet_CHIP8 - Debug ]----------"
	@cd "Projet_CHIP8" && "$(MAKE)" -f  "Projet_CHIP8.mk"
clean:
	@echo "----------Cleaning project:[ Projet_CHIP8 - Debug ]----------"
	@cd "Projet_CHIP8" && "$(MAKE)" -f  "Projet_CHIP8.mk" clean
