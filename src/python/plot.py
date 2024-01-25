import matplotlib.pyplot as plt
import json
import os.path as path

cwd = path.dirname(__file__)


def build_tree(levelNodes: list, level):

    n = len(levelNodes)

    if n == 0:
        return

    nextLevelNodes = []
    x = length // (n + 1)
    y = (length - level)*4
    for i in levelNodes:

        for node in tree_data[i[0]]:
            nextLevelNodes.append([node, x, y])

        ax.text(x, y, i[0][0:10], ha='center', va='center',
                bbox={"facecolor": 'white', "edgecolor": 'white'}, fontsize=7, c="salmon")

        ax.plot([x, i[1]], [y, i[2]], 'k-', c="skyblue")

        x += length // (n + 1)

    build_tree(nextLevelNodes, level+1)


with open(path.join(cwd, "../../data/tree_data.json"), 'r') as jsonFile:
    tree_data = json.load(jsonFile)

fig, ax = plt.subplots()
ax.axis('off')

root = list(tree_data.keys())[1]
length = tree_data['size']*1_000


nextLevelNodes = []
x = length // 2
y = (length)*4

for node in tree_data[root]:
    nextLevelNodes.append([node, x, y])

ax.text(x, y, root[0:10], ha='center', va='center', bbox={
    "facecolor": 'white', "edgecolor": 'white'}, fontsize=7, c="salmon")


build_tree(nextLevelNodes, 1)
plt.tight_layout()
plt.show()
