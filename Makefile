#(doit correspondre au add_executable du CMakeLists.txt)
EXE = CreatureSimulator
BUILD_DIR = build

.PHONY: run clean

#Configure -> Compile -> Lance
run:
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)
	./$(BUILD_DIR)/$(EXE)

# Nettoyage
clean:
	rm -rf $(BUILD_DIR)

# Sauvegarde Git
# Usage: make save msg="Mon message"

files = .
save:
	@git add $(files)
	@git commit -m "$(msg)"
	@git push
	@echo "--- Commit $(GIT_VERSION) poussé ! ---"

# Mise à jour
pull:
	git pull