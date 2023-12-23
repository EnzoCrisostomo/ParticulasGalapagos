#pragma once
#include "Galapagos/Components/ParticleEmmiter.hpp"

namespace ParticlePreset {
    const ParticleConfig Fire = {
		.position = {0, 0},
		.velocity = {0, -100},
		.velocityVariation = {60, 20},
		.startColor = {245, 228, 122, 255},
		.endColor = {255, 91, 10, 255},
		.startSize = 8,
		.endSize = 0,
		.sizeVariation = 2,
		.lifeTime = 2,
		.rate = 80
	};
	const ParticleConfig Snow = {
		.position = {0, 0},
		.velocity = {0, 80},
		.velocityVariation = {20, 20},
		.startColor = {180, 255, 255, 255},
		.endColor = {49, 228, 247, 255},
		.startSize = 50,
		.endSize = 2,
		.sizeVariation = 1,
		.lifeTime = 10,
		.rate = 50
	};
	const ParticleConfig Rain = {
		.position = {0, 0},
		.velocity = {40, 500},
		.velocityVariation = {20, 20},
		.startColor = {180, 255, 255, 150},
		.endColor = {49, 228, 247, 150},
		.startSize = 3,
		.endSize = 2,
		.sizeVariation = 1,
		.lifeTime = 10,
		.rate = 300
	};
	const ParticleConfig Explosion = {
		.position = {0, 0},
		.velocity = {0, 0},
		.velocityVariation = {500, 500},
		.startColor = {245, 171, 73, 255},
		.endColor = {245, 213, 73, 255},
		.startSize = 5,
		.endSize = 1,
		.sizeVariation = 3,
		.lifeTime = 2,
		.rate = 300
	};
};