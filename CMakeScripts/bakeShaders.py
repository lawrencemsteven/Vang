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


# Get shader varible names
for i in range(len(shaders)):
	shaderNames.append(shaders[i].upper())
	shaderNames[i] = shaderNames[i].replace(os.sep, "_")
	shaderNames[i] = re.sub('[^a-zA-Z0-9]', '_', shaderNames[i])


# Output file
bakedShadersFile = open(os.path.join(toLocation, "bakedShaders.h"), "w")


# Pragma
bakedShadersFile.write("#pragma once\n\n")


# Namespace Definition
bakedShadersFile.write("namespace Vang::gfx::Shaders {\n\n")


# Write preprocessor definitions
bakedShadersFile.write("#ifdef VANG_RENDERING_PLANEASSISTED\n")
bakedShadersFile.write("\tconst char* SHADER_PREPROCESSOR_DEFINITIONS = \"#define VANG_RENDERING_PLANEASSISTED\\n\";\n")
bakedShadersFile.write("#elif VANG_RENDERING_CUBOID\n")
bakedShadersFile.write("\tconst char* SHADER_PREPROCESSOR_DEFINITIONS = \"#define VANG_RENDERING_CUBOID\\n\";\n")
bakedShadersFile.write("#elif VANG_RENDERING_OCTREE\n")
bakedShadersFile.write("\tconst char* SHADER_PREPROCESSOR_DEFINITIONS = \"#define VANG_RENDERING_OCTREE\\n\";\n")
bakedShadersFile.write("#endif\n\n")


# Write shaders to output file
for i in range(len(shaders)):
	bakedShadersFile.write("\tconst char* SHADER_" + shaderNames[i] + " = *SHADER_PREPROCESSOR_DEFINITIONS + R\"(\n")

	# Shader Data
	shaderFile = open(os.path.join(fromLocation, shaders[i] + ".glsl"), "r")
	for line in shaderFile:
		bakedShadersFile.write(line)
	shaderFile.close()

	bakedShadersFile.write("\n)\";\n\n")
bakedShadersFile.write("}")
bakedShadersFile.close()