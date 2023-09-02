import os

p1 = "5colis30capacite.txt"
p2 = "p2.txt"

# Clear les fichiers
open("resultat.txt", "w").close()
open("output.txt", "w").close()


# 100 réplications
for i in range(1, 11):
    os.system(f"./build/TP5 {i} ./data/{p1} ./data/{p2} >> resultat.txt")

# On génére la solution combinée
os.system(f"./build/TP5 -1 resultat.txt ./data/{p2} >> output.txt")

# # On calcule l'écart relatif
# f = open("output.txt", "r")
# text = f.read()
# f.close()

# lines = text.split("\n")  # séparer le texte en lignes
# dst_heuris = int(lines[0].split(" ")[-1])
# dst_exacte = int(lines[1].split(" ")[-1])

# delta = ((dst_exacte - dst_heuris) / dst_exacte)*100
# delta = round(delta, 3)
# print(f"Delta: {delta}%")