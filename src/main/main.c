 
/* src/main/main.c */
#include <stdio.h>

int main(void) {
    printf("Hybrid firmware running.\\n");
    return 0;
}
 

EOF

        chmod +x scripts/generate_results.sh

        # ----------------------------
        # Pre-commit Configuration
        # ----------------------------

        cat <<EOF > .pre-commit-config.yaml
repos:
  - repo: https://github.com/psf/black
    rev: 23.12.1
    hooks:
      - id: black

  - repo: https://github.com/astral-sh/ruff-pre-commit
    rev: v0.1.6
    hooks:
      - id: ruff
EOF

        "$VENV_DIR/bin/pre-commit" install

        # ----------------------------
        # Git Init
        # ----------------------------

        git init
        git add .
        git commit -m "Initial project structure"

        if [ "$REMOTE_TYPE" == "github" ]; then
            gh repo create "$PROJECT_NAME" "$VISIBILITY" --source=. --push
        elif [ "$REMOTE_TYPE" == "gitlab" ]; then
            glab repo create "$PROJECT_NAME" "$VISIBILITY" --source=. --push
        fi

        echo "Project created successfully."
        ;;