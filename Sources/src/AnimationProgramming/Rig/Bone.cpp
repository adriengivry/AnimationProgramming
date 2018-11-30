/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#include "AnimationProgramming/Rig/Bone.h"
#include "AnimationProgramming/Tools/IniManager.h"

AnimationProgramming::Rig::Bone::Bone(const std::string& p_name, uint32_t p_index, AltMath::Vector3f p_localPosition, AltMath::Quaternion p_localRotation) :
	m_name(p_name),
	m_index(p_index),
	m_parent(nullptr),
	m_transform(p_localPosition, p_localRotation),
	m_defaultTransform(p_localPosition, p_localRotation)
{}

void AnimationProgramming::Rig::Bone::SetParent(Bone& p_parent)
{
	m_parent = &p_parent;
	m_transform.SetParent(p_parent.GetTransform());
	m_defaultTransform.SetParent(p_parent.GetDefaultTransform());
}

void AnimationProgramming::Rig::Bone::SetRelativePosition(AltMath::Vector3f p_localPosition)
{
	m_transform.SetPosition(m_defaultTransform.GetLocalPosition() + p_localPosition);
}

void AnimationProgramming::Rig::Bone::SetRelativeRotation(AltMath::Quaternion p_localRotation)
{
	m_transform.SetRotation(m_defaultTransform.GetLocalRotation() * p_localRotation);
}

void AnimationProgramming::Rig::Bone::SetRelativePositionAndRotation(AltMath::Vector3f p_localPosition, AltMath::Quaternion p_localRotation)
{
	m_transform.GenerateMatrices(m_defaultTransform.GetLocalPosition() + p_localPosition, m_defaultTransform.GetLocalRotation() * p_localRotation);
}

void AnimationProgramming::Rig::Bone::ResetPositionAndRotation()
{
	SetRelativePositionAndRotation(AltMath::Vector3f::Zero, AltMath::Quaternion(0.0f, 0.0f, 0.0f, 1.0f));
}

bool AnimationProgramming::Rig::Bone::IsRoot() const
{
	return !m_parent;
}

bool AnimationProgramming::Rig::Bone::IsIK() const
{
	return !(m_name.find("ik") == std::string::npos);
}

bool AnimationProgramming::Rig::Bone::HasParent() const
{
	return m_parent != nullptr;
}

AnimationProgramming::Rig::Bone& AnimationProgramming::Rig::Bone::GetParent()
{
	return *m_parent;
}

uint32_t AnimationProgramming::Rig::Bone::GetIndex()
{
	return m_index;
}

AnimationProgramming::Data::Transform & AnimationProgramming::Rig::Bone::GetTransform()
{
	return m_transform;
}

AnimationProgramming::Data::Transform & AnimationProgramming::Rig::Bone::GetDefaultTransform()
{
	return m_defaultTransform;
}