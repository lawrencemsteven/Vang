import os
import re
import sys

fromLocation = sys.argv[1]
toLocation = sys.argv[2]

if not os.path.exists(toLocation):
	os.makedirs(toLocation)

shaders = []
shaderNames = []
shader_dirs = []
roots = []

# Get All Files
def getFiles(startLoc, relLoc = ""):
	for file in os.listdir(os.path.join(startLoc, relLoc)):
		if os.path.isfile(os.path.join(startLoc, relLoc, file)):
			if os.path.splitext(file)[-1] == ".glsl":
				shaders.append(os.path.join(relLoc, os.path.splitext(file)[0]))
		else:
			getFiles(startLoc, os.path.join(relLoc, file))
getFiles(fromLocation)

for i in range(len(shaders)):
	shaderNames.append(shaders[i].upper())
	shaderNames[i] = shaderNames[i].replace(os.sep, "_")
	shaderNames[i] = re.sub('[^a-zA-Z0-9]', '_', shaderNames[i])

bakedShadersFile = open(os.path.join(toLocation, "bakedShaders.h"), "w")
# bakedShadersFile.write(fromLocation + "\n\n" + toLocation + "\n")
# for i in range(len(shaders)):
# 	bakedShadersFile.write(shaders[i] + " :: " + shaderNames[i] + "\n")
# bakedShadersFile.close()

bakedShadersFile.write("namespace Vang::gfx::Shaders {\n")
for i in range(len(shaders)):
	bakedShadersFile.write("const char* SHADER_" + shaderNames[i] + " = R\"(\n")
	
	shaderFile = open(os.path.join(fromLocation, shaders[i] + ".glsl"), "r")
	for line in shaderFile:
		bakedShadersFile.write(line)
	shaderFile.close()

	bakedShadersFile.write("\n)\";\n\n")
bakedShadersFile.write("}")
bakedShadersFile.close()

# std::string shader_src = R"(
# //shader cods
# //more shader
# //even more code
# //you don't  need to add \n every line with the R prefix 
# )";