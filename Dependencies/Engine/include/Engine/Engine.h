#ifndef __ENGINE_H__
#define __ENGINE_H__

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport) 
#else
#define ENGINE_API __declspec(dllimport) 
#endif


ENGINE_API void			Run( class ISimulation* pSimulation, unsigned int width, unsigned int height );

// Array of matrices (matrices = 16 floats) sent to GPU (in the same order than bones are ordered in skeleton)
ENGINE_API void			SetSkinningPose( const float* boneMatrices, size_t boneCount );

ENGINE_API size_t		GetSkeletonBoneCount();

ENGINE_API const char*	GetSkeletonBoneName(int boneIndex);

ENGINE_API int			GetSkeletonBoneIndex(const char* name);

// return -1 if the bone doesn't have parent
ENGINE_API int			GetSkeletonBoneParentIndex(int boneIndex);

// return local transform (ie relative to the parent) of the bone in the bind pose (or rest pose, also called T-pose)
ENGINE_API void			GetSkeletonBoneLocalBindTransform(int boneIndex, float& posX, float& posY, float& posZ, float& quatW, float& quatX, float& quatY, float& quatZ);

ENGINE_API size_t		GetAnimKeyCount(const char* animName);

// return the transform relative to the bind pose
// there are two animations named "ThirdPersonWalk.anim" and "ThiedPersonRun.anim"
ENGINE_API void			GetAnimLocalBoneTransform(const char* animName, int boneIndex, int keyFrameIndex, float& posX, float& posY, float& posZ, float& quatW, float& quatX, float& quatY, float& quatZ);

ENGINE_API void			DrawLine(float x0, float y0, float z0, float x1, float y1, float z1, float r, float g, float b);


#endif