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
		glTexImage3D(GL_TEXTURE_3D, 0, GL_RG32UI, 576, 576, 576, 0, GL_RG_INTEGER, GL_UNSIGNED_INT,
					 NULL);
		glBindImageTexture(1, m_texture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RG32UI);
	}

	void BlockBuffer::update() {
		glBindTexture(GL_TEXTURE_3D, m_texture);
		const auto& chunkRenderer	  = Vang::getPlayer().getCamera().getChunkRenderer();
		const uint32_t renderDiameter = chunkRenderer.getRenderDiameter();

		const auto& chunks	  = chunkRenderer.getChunks();
		uint32_t chunkCounter = 0;
		for (uint32_t x = 0; x < renderDiameter; x++) {
			for (uint32_t y = 0; y < renderDiameter; y++) {
				for (uint32_t z = 0; z < renderDiameter; z++) {
					const auto& chunk = chunks[chunkCounter];
					if (chunk->getDirty()) {
						chunk->greedyCuboidCompilation();
						chunk->setDirty(false);
						glTexSubImage3D(GL_TEXTURE_3D, 0, x * 64, z * 64, y * 64, 64, 64, 64,
										GL_RG_INTEGER, GL_UNSIGNED_INT,
										chunk->getAllBlocks().data());
					}
					chunkCounter += 1;
				}
			}
		}
	}

}