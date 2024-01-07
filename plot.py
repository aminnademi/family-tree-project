import matplotlib.pyplot as plt
import json


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

        ax.text(x, y, i[0], ha='center', va='center',
                bbox={"facecolor": 'white', "edgecolor": 'white'})

        ax.plot([x, i[1]], [y, i[2]], 'k-')

        x += length // (n + 1)

    build_tree(nextLevelNodes, level+1)


with open('tree_data.json', 'r') as jsonFile:
    tree_data = json.load(jsonFile)

fig, ax = plt.subplots()
ax.axis('off')

root = list(tree_data.keys())[1]
length = tree_data['size']


nextLevelNodes = []
x = length // 2
y = (length)*4

for node in tree_data[root]:
    nextLevelNodes.append([node, x, y])

ax.text(x, y, root, ha='center', va='center', bbox={
    "facecolor": 'white', "edgecolor": 'white'})


build_tree(nextLevelNodes, 1)
plt.tight_layout()
plt.show()
