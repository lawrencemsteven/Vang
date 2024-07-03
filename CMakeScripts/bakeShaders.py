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


# Create Output files
bakedShadersFile = open(os.path.join(toLocation, "bakedShaders.h"), "w")




#################
## HEADER FILE ##
#################
# Get Header File
bakedShadersFile = open(os.path.join(toLocation, "bakedShaders.h"), "w")


# Pragma
bakedShadersFile.write("#pragma once\n\n")


# Namespace Definition
bakedShadersFile.write("namespace Vang::gfx::Shaders {\n\n")


# Class Definition
bakedShadersFile.write("\tclass BakedShaders {\n")
bakedShadersFile.write("\tpublic:\n")
bakedShadersFile.write("\t\tBakedShaders() = delete;\n")
bakedShadersFile.write("\t\t~BakedShaders() = delete;\n\n")


# Method Definitions
for shaderName in shaderNames:
	bakedShadersFile.write("\t\tstatic std::string GET_" + shaderName + "();\n")
bakedShadersFile.write("\n")


# Private Shader Variables
bakedShadersFile.write("\tprivate:\n")
bakedShadersFile.write("\t\tstatic const char* SHADER_VERSION;\n")
bakedShadersFile.write("\t\tstatic const char* PREPROCESSOR_DEFINITIONS;\n")
for shaderName in shaderNames:
	bakedShadersFile.write("\t\tstatic const char* " + shaderName + ";\n")


# Close Class, Namespace, and File
bakedShadersFile.write("\t};\n\n")
bakedShadersFile.write("}")
bakedShadersFile.close()




#################
## SOURCE FILE ##
#################
# Get Source File
bakedShadersFile = open(os.path.join(toLocation, "bakedShaders.cpp"), "w")


# Include Header
bakedShadersFile.write("#include \"bakedShaders.h\"\n\n")


# Namespace Definition
bakedShadersFile.write("namespace Vang::gfx::Shaders {\n\n")


# Method Definitions
for shaderName in shaderNames:
	bakedShadersFile.write("\tstd::string BakedShaders::GET_" + shaderName + "() {\n")
	bakedShadersFile.write("\t\tstd::string output{};\n")
	bakedShadersFile.write("\t\toutput += PREPROCESSOR_DEFINITIONS;\n")
	bakedShadersFile.write("\t\toutput += " + shaderName + ";\n")
	bakedShadersFile.write("\t\treturn output;\n")
	bakedShadersFile.write("\t}\n\n")


# Preprocessor Definitions
bakedShadersFile.write("\tconst char* BakedShaders::PREPROCESSOR_DEFINITIONS = \"\";\n\n")


# Shader Definitions
for i in range(len(shaders)):
	bakedShadersFile.write("\tconst char* BakedShaders::" + shaderNames[i] + " = R\"(\n")

	# Shader Data
	shaderFile = open(os.path.join(fromLocation, shaders[i] + ".glsl"), "r")
	for line in shaderFile:
		bakedShadersFile.write(line)
	shaderFile.close()

	bakedShadersFile.write("\n)\";\n\n")

# Close Namespace and File
bakedShadersFile.write("}")
bakedShadersFile.close()