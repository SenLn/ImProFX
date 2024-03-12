// framework_particle_interface.

#ifndef _FRAMEWORK_PARTICLE_INTERFACE_H
#define _FRAMEWORK_PARTICLE_INTERFACE_H

#include "../improfx_log/framework_log.hpp"
#include "../improfx_renderer/framework_imfxgl_resource.hpp"

enum ParticleCreateMode {
	PTCpoints = 1 << 1, // ��.
	PTCdrift  = 1 << 2, // Ʈ�� [Ч��]
	PTCcircle = 1 << 3, // Բ�� [��ɢ]
	PTCsquare = 1 << 4, // ���� [��ɢ]
};

// [2023_11_26](1): ImProFx�������ϵͳ�ӿ�.
namespace IFC_PARTC {

	enum ParticleMode {
		ParticleStatic  = 2, // no_update vector,position.
		ParticleDynamic = 4  // update vector,position,color.
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
			ParticleModeType (ParticleDynamic)
		{}
	};
	
	// ��������Ч��(ʹ��[���ȷֲ�]�����ģ��).
	class ParticleCreateBase {
	public:
		// particle generation number[n > 8].
		virtual void ConfigCreateNumber(float number) = 0;
		
		virtual void ConfigCreateMode(ParticleCreateMode mode) = 0;             // ����ģʽ.
		virtual void ConfigLifeDispersion(Vector2T<float> rand_limit_life) = 0; // �������.

		// ���ӿռ�: vector.xy scale[min,max], position.xy scale[min,max], color_system.xyz switch[rd,rd,rd].
		// "OffsetPosition" ����ƫ��λ��(����ƫ��).
		virtual void ConfigRandomDispersion(
			Vector2T<float> rand_limit_vector,
			Vector2T<float> rand_limit_position,
			Vector3T<bool>  color_system,
			Vector3T<float> offset_position
		) = 0;

		virtual void CreateAddParticleDataset(std::vector<ParticleAttributes>& data) = 0;
	};

	struct ParticleSystemState {
		// real-time status.
		size_t DarwParticlesNumber;
		size_t DarwDatasetSize;
	};

	// ParticleShader ������ϵͳ�Լ�����(���ܺ���ɫ���޹�).
	class ParticleBase {
	public:
		virtual void ParticleCreate(ParticleCreateBase* generator) = 0;

		// get particle system state.
		virtual ParticleSystemState GetParticleState() = 0;
		// get particle render texture handle.
		virtual uint32_t GetParticleRenderHandle() = 0;
		// get particle dataset(vector) pointer.
		virtual std::vector<ParticleAttributes>* GetParticleDataset() = 0;

		// particle system update.
		virtual void _UPDATE_ParticleSystem() = 0;
		virtual ~ParticleBase() = default;
	};
}

#endif
