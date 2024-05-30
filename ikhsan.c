#include "global.h"
#include "ariq.h"
#include "ikhsan.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void printTreeHelper(FILE *file, addressTree node, int space, char* prefix) {
    int COUNT = 25; // Space between levels
    if (node == NULL) {
        return;
    }

    space += COUNT;

    printTreeHelper(file, node->right, space, "+");

    fprintf(file, "\n");
    for (int i = COUNT; i < space; i++) {
        fprintf(file, " ");
    }

    if (space == COUNT) {
        fprintf(file, "[Root] ");
    }

    fprintf(file, "%s%s\n", prefix, node->info);

    if (node->left != NULL) {
        printTreeHelper(file, node->left, space, "-");
    }
}

// Function to print tree structure to a file
void printTreeToFile(addressTree rootTree, const char* fileName) {
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    printTreeHelper(file, rootTree, 0, "");
    fclose(file);
}

// Function to print tree structure to CLI
void printTreeHelperCLI(addressTree node, int level, int isLast, int *path) {
    if (node == NULL) {
        return;
    }

    // Print indentation for the current level
    for (int i = 0; i < level - 1; i++) {
        if (path[i]) {
            printf("|   ");
        } else {
            printf("    ");
        }
    }

    if (level > 0) {
        if (isLast) {
            printf("`-- ");
        } else {
            printf("|-- ");
        }
    }

    // Print the question or answer
    printf("%s\n", node->info);

    // Mark this node as visited in the path
    path[level - 1] = !isLast;

    // Print the left subtree
    if (node->left || node->right) {
        path[level] = 1;  // Ensure the next level gets a vertical line if there are more siblings
    }
    printTreeHelperCLI(node->left, level + 1, node->right == NULL, path);

    // Print the right subtree
    printTreeHelperCLI(node->right, level + 1, 1, path);
}

// Function to print tree structure to CLI
void printTree(addressTree rootTree) {
    if (rootTree == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    // Create a path array to track where to print '|'
    int path[1000] = {0};

    // Print the root node
    printf("%s\n", rootTree->info);

    // Call printTreeHelperCLI for subtrees
    printTreeHelperCLI(rootTree->left, 1, 0, path);
    printTreeHelperCLI(rootTree->right, 1, 1, path);
}



void deleteTree(addressTree *rootTree) {
    if (*rootTree != NULL) {
        // Hapus anak kiri
        deleteTree(&((*rootTree)->left));
        // Hapus anak kanan
        deleteTree(&((*rootTree)->right));
        // Hapus node saat ini
        free(*rootTree);
        // Atur referensi ke node saat ini menjadi NULL
        *rootTree = NULL;
    }
}


void printAsciiArt() {
	setTextColor(15, 0);  
    const char *asciiArt[] = {
        "███╗░░░███╗██╗███╗░░██╗██████╗░  ███╗░░░███╗░█████╗░░██████╗████████╗███████╗██████╗░",
        "████╗░████║██║████╗░██║██╔══██╗  ████╗░████║██╔══██╗██╔════╝╚══██╔══╝██╔════╝██╔══██╗",
        "██╔████╔██║██║██╔██╗██║██║░░██║  ██╔████╔██║███████║╚█████╗░░░░██║░░░█████╗░░██████╔╝",
        "██║╚██╔╝██║██║██║╚████║██║░░██║  ██║╚██╔╝██║██╔══██║░╚═══██╗░░░██║░░░██╔══╝░░██╔══██╗",
        "██║░╚═╝░██║██║██║░╚███║██████╔╝  ██║░╚═╝░██║██║░░██║██████╔╝░░░██║░░░███████╗██║░░██║",
        "╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═════╝░  ╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═════╝░░░░╚═╝░░░╚══════╝╚═╝░░╚═╝",
        NULL
    };

    int columns, rows;
    getConsoleSize(&columns, &rows);
    int artHeight = 0;
    for (int i = 0; asciiArt[i] != NULL; i++) {
        artHeight++;
    }

    int startY = (rows - artHeight) / 3;
    if (startY < 0) startY = 0; // Pastikan tidak negatif

    for (int i = 0; asciiArt[i] != NULL; i++) {
        printCentered(asciiArt[i], startY + i);
    }
}

void printAsciiBanner() {
    const char *akinator_art[] = {
        "                                           .***-                      \n",
        "                                           ...%@-                     \n",
        "                                  .::...:: :%@*-                      \n",
        "                           :---::.        :-%%                        \n",
        "                        -:+---:        ....:-=++-                     \n",
        "                       * -.   :=++=--:.          :-:                  \n",
        "                      :=.  :=+=+ .=*-.             .=                 \n",
        "                      :.:  :**++    ===:            :-                \n",
        "                       --    .-==+***###*++-        :+                \n",
        "                        =-=+**++++++*+++*+*%@+.     -+                \n",
        "                         .####+++***##%%%#++@@#*#*#=%.                \n",
        "                          ###*+++###*##**+*+%***#+=:-                 \n",
        "                           #=%@***++=%%+*+++*#@##%=:                  \n",
        "                           +++#++++*+**++++++##*+.                    \n",
        "                           ++*#*+#*#*++++++++*+%                      \n",
        "                           *+%*#%%%###+++++++++:                      \n",
        "                           +++*++*++++++*+++*+.                       \n",
        "                            -+*+@#++*+++****+#+                       \n",
        "                               *@#@******+++#**                       \n",
        "                             :-*@#%*+++*+**++*=.                      \n",
        "                         =+++=*#+%*+++*+++++**+++==-:                 \n",
        "                       .*+======*#+++**++++++========+=:              \n",
        "                      .*=+++====**+++#+=++++============+=            \n",
        "                     :*++*+===++*#+++%++++===============+            \n",
        "                    -+++*+++=+++*####++=================+-            \n",
        "                   -+++*#####+=======+++=========++=====*             \n",
        "                 :++++#***#*+#++================+*+====+:             \n",
        "               .=+++****##*##%*#********=====+++*+====+=              \n",
        "             .=+=+++===+#+**+++++++**++**+++*++*+=====+               \n",
        "             =+=======+#++++*****++=++******+**+=====*.               \n",
        "             .#++++++=*=+****+=============+**++====+-                \n",
        "              .*+++++++*%%*+%================+=+====*                 \n",
        "                =*++++%%%*=+*+=+++==================#                 \n",
        "                 =+++*%%#==+*+++++++++++++++++++=++++                 \n",
        "                  +*+##%=+==*+++++++++++++++++++*+=-                  \n",
        "                   *+*%+ *+=*++++++**++++++*:...                      \n",
        "                   .++=  :*=+*+++*++====+*=                           \n",
        "                          ++=++*+======++.                            \n",
        "                           *+=========+=                   .:--::     \n",
        "                           =*=======+*.               .:=++++++++*+   \n",
        "                            ++======+              -=+++++=--:-*++++  \n",
        "                             =+====+=     .:.   :=++=+*-        **=   \n",
        "                              :*+===+=.  =%%+*+++==+*+.        -+     \n",
        "                               .*++===+*++**++===+##=+*.       *      \n",
        "                                 =#++++=======++%@%#+*-=*--+#%**-     \n",
        "                                   :==++******%@@@@@@@%%%%%%*:        \n",
        "                                              =%@@@@@@@@@@*.          \n",
        "                                                -*@%%%*+-             \n",
        "                                                =%%#***:              \n"
    };

    for(int i = 0; i < sizeof(akinator_art) / sizeof(akinator_art[0]); i++) {
        fputs(akinator_art[i], stdout);
    }

}
