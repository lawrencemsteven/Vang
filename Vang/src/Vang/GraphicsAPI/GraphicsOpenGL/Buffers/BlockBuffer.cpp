#include "BlockBuffer.h"

#include "Vang.h"

namespace Vang::gfx::OpenGL {

	void BlockBuffer::initialize() {
		glGenTextures(1, &m_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_3D, m_texture);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage3D(GL_TEXTURE_3D, 0, GL_R32UI, 512, 512, 512, 0, GL_RED_INTEGER, GL_UNSIGNED_INT,
					 NULL);
		glBindImageTexture(1, m_texture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_R32UI);
	}

	void BlockBuffer::update() {
		auto& currentWorld = Vang::getCurrentWorld();

		if (!currentWorld.getDirty()) {
			return;
		}

		glBindTexture(GL_TEXTURE_3D, m_texture);
		for (int32_t x = 0; x < 8; x++) {
			for (int32_t y = 0; y < 8; y++) {
				for (int32_t z = 0; z < 8; z++) {
					auto chunk = currentWorld.loadChunk({x, y, z});
					glTexSubImage3D(GL_TEXTURE_3D, 0, x * 64, z * 64, y * 64, 64, 64, 64,
									GL_RED_INTEGER, GL_UNSIGNED_INT, chunk->getAllBlocks().data());
				}
			}
		}

		currentWorld.setDirty(false);
	}

}