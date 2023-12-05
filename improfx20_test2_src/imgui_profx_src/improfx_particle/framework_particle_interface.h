// framework_particle_interface.
// [INTERFACE].

#ifndef _FRAMEWORK_PARTICLE_INTERFACE_H
#define _FRAMEWORK_PARTICLE_INTERFACE_H
#include "../improfx_log/framework_log.hpp"

enum ParticleCreateMode {
	ptcPoints   = 1 << 1, // ��.
	ptcCircle   = 1 << 2, // Բ�� [��ɢ]
	ptcSquare   = 1 << 3, // ���� [��ɢ]
	ptcTriangle = 1 << 4, // ������ [��ɢ]
	ptcDrift    = 1 << 5  // Ʈ�� [Ч��]
};

// [2023_11_26](1): ImProFx�������ϵͳ�ӿ�.
namespace IFC_PARTC {

	enum ParticleMode {
		particle_static  = 2, // no_update vector,position.
		particle_dynamic = 4  // update vector,position,color.
	};

	struct ParticleAttributes {
		Vector3T<float> ParticleVector;
		Vector3T<float> ParticlePosition;
		Vector4T<float> ParticleColor;

		float ParticleLife;
		ParticleMode ParticleModeType;

		constexpr ParticleAttributes() :
			ParticleVector   ({}),
			ParticlePosition ({}),
			ParticleColor    ({}),
			ParticleLife     (0.0f),
			ParticleModeType (particle_dynamic)
		{}
	};
	
	// ��������Ч��(ʹ��[���ȷֲ�]�����ģ��).
	class ParticleCreateBase {
	public:
		// particle generation number[n > 8].
		virtual void ConfigCreateNumber(float Number) = 0;
		// ����ģʽ: "ParticleCreateMode"
		virtual void ConfigCreateMode(ParticleCreateMode Mode) = 0;
		// ��������: life.xy life_timer[min,max]. 
		virtual void ConfigLifeDispersion(Vector2T<float> LifeRandLimit) = 0;

		// ���ӿռ�: vector.xy scale[min,max], position.xy scale[min,max], color_system.xyz switch[rd,rd,rd].
		// "OffsetPosition" ����ƫ��λ��(����ƫ��).
		virtual void ConfigRandomDispersion(
			Vector2T<float> VecRandLimit,
			Vector2T<float> PosRandLimit,
			Vector3T<bool>  ColorSystem,
			Vector3T<float> OffsetPosition
		) = 0;

		virtual void CreateAddParticleDataset(std::vector<ParticleAttributes>& Data) = 0;
	};

	struct ParticleSystemState {
		size_t DarwParticlesNumber;
		size_t DarwDatasetSize;
	};

	// particle shader ������ϵͳ�Լ�����(���ܺ�����Ⱦ���޹�).
	class ParticleBase {
	public:
		virtual bool ParticleSystemUpdate() = 0;
		virtual void ParticleCreate(ParticleCreateBase* Generator) = 0;

		// get particle system state.
		virtual ParticleSystemState GetParticleState() = 0;
		// get particle render texture handle.
		virtual uint32_t GetParticleRenderHandle() = 0;
		// get particle dataset(vector) pointer.
		virtual std::vector<ParticleAttributes>* GetParticleDataset() = 0;
		virtual ~ParticleBase() = default;
	};
}

#endif
