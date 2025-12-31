# Change le nom ici pour correspondre à ton CMakeLists.txt
EXE = QuadPhysicsSim
BUILD_DIR = build

.PHONY: run clean snapshot

# Configure -> Compile -> Lance
run:
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)
	./$(BUILD_DIR)/$(EXE)

# Nettoyage
clean:
	rm -rf $(BUILD_DIR)

# Snapshot: Tree + Contenu des fichiers
# Note: Nécessite que 'tree' soit installé (sudo apt install tree)
snapshot:
	@echo "Génération du snapshot..."
	# 1. Écrit l'arborescence (ignore build et .git)
	tree -I "$(BUILD_DIR)|.git|snapshot.txt" > snapshot.txt
	@echo "" >> snapshot.txt
	@echo "################################################" >> snapshot.txt
	@echo "#              CONTENU DES FICHIERS             #" >> snapshot.txt
	@echo "################################################" >> snapshot.txt
	# 2. Trouve tous les fichiers, ignore build/.git/snapshot.txt, et ajoute leur contenu
	@find . -type f -not -path "./$(BUILD_DIR)/*" -not -path "./.git/*" -not -name "snapshot.txt" | while read file; do \
		echo "" >> snapshot.txt; \
		echo "========================================" >> snapshot.txt; \
		echo "FICHIER: $$file" >> snapshot.txt; \
		echo "========================================" >> snapshot.txt; \
		cat "$$file" >> snapshot.txt; \
	done
	@echo "Terminé ! Résultat dans snapshot.txt"

# Sauvegarde Git
files = .
save:
	@git add $(files)
	@git commit -m "$(msg)"
	@git push
	@echo "--- Commit $(GIT_VERSION) poussé ! ---"

# Mise à jour
pull:
	git pull