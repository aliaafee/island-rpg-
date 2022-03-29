import os

files = os.listdir("vegetation")

for file in files:
    if file[-4:len(file)] == ".png":
        spritefile = file.replace(".png", ".sprite")
        print(spritefile)

        with open(f"sprites/{spritefile}", 'w') as f:
            lines = []
            lines.append(f"texture str graphics/vegetation/{file}\n")
            lines.append("origin vec2 110,212\n")
            lines.append("size vec3 5,5,5\n")
            f.writelines(lines)
