/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#include "AnimationProgramming/Core/AnimationEngine.h"
#include "AnimationProgramming/Simulations/CSimulation.h"
#include "AnimationProgramming/Tools/IniManager.h"
#include "AnimationProgramming/Tools/Math.h"

AnimationProgramming::Simulations::CSimulation::CSimulation() :
	m_animator(m_skeleton),
	m_timelineDrawer(5.0f, 10.0f, 10, AltMath::Vector3f(0.0f, 0.0f, 1.0f)),
	m_skeletonDrawer(Data::Color::Cyan, Data::Color::Blue, Data::Color::Yellow, 3.0f)
{}

void AnimationProgramming::Simulations::CSimulation::Init()
{
	Rendering::Renderer::EnableAlphaMode(Tools::IniManager::Rendering->Get<bool>("enable_alpha"));
	Rendering::Renderer::SetDrawMode(Tools::IniManager::Rendering->Get<bool>("enable_wireframe") ? Rendering::EDrawMode::WIREFRAME : Rendering::EDrawMode::NORMAL);

	LoadAnimationsInfo();
	CreateCustomAnimations();
	CreateAnimationInstances();
	CreateSkeleton();
	PlayDefaultAnimation();
	PrintHelpTip();
}

void AnimationProgramming::Simulations::CSimulation::LoadAnimationsInfo()
{
	m_walkAnimation = std::make_unique<Animation::AnimationInfo>("ThirdPersonWalk.anim");
	m_runAnimation = std::make_unique<Animation::AnimationInfo>("ThirdPersonRun.anim");
}

void AnimationProgramming::Simulations::CSimulation::CreateCustomAnimations()
{
	/* Dab animation */
	{
		m_dabAnimation = std::make_unique<Animation::AnimationInfo>(2);

		uint32_t rightShoulder = Core::AnimationEngine::GetSkeletonBoneIndex("upperarm_r");
		uint32_t leftShoulder = Core::AnimationEngine::GetSkeletonBoneIndex("upperarm_l");
		uint32_t leftElbow = Core::AnimationEngine::GetSkeletonBoneIndex("lowerarm_l");
		uint32_t neck = Core::AnimationEngine::GetSkeletonBoneIndex("neck_01");
		uint32_t body = Core::AnimationEngine::GetSkeletonBoneIndex("spine_02");

		AltMath::Quaternion rightShoulderRotation = Tools::Math::CreateQuaternionFromEuler(AltMath::Vector3f(0.0f, -80.0f, 0.0f));
		AltMath::Quaternion leftShoulderRotation = Tools::Math::CreateQuaternionFromEuler(AltMath::Vector3f(30.0f, 40.0f, -110.0f));
		AltMath::Quaternion leftElbowRotation = Tools::Math::CreateQuaternionFromEuler(AltMath::Vector3f(0.0f, 0.0f, -70.0f));
		AltMath::Quaternion neckRotation = Tools::Math::CreateQuaternionFromEuler(AltMath::Vector3f(70.0f, 0.0f, -50.0f));
		AltMath::Quaternion bodyRotation = Tools::Math::CreateQuaternionFromEuler(AltMath::Vector3f(0.0f, 20.0f, 0.0f));

		m_dabAnimation->SetBoneRelativeTransformation(rightShoulder, 1, std::make_pair(AltMath::Vector3f::Zero, rightShoulderRotation));
		m_dabAnimation->SetBoneRelativeTransformation(leftShoulder, 1, std::make_pair(AltMath::Vector3f::Zero, leftShoulderRotation));
		m_dabAnimation->SetBoneRelativeTransformation(leftElbow, 1, std::make_pair(AltMath::Vector3f::Zero, leftElbowRotation));
		m_dabAnimation->SetBoneRelativeTransformation(neck, 1, std::make_pair(AltMath::Vector3f::Zero, neckRotation));
		m_dabAnimation->SetBoneRelativeTransformation(body, 1, std::make_pair(AltMath::Vector3f::Zero, bodyRotation));
	}

	/* Squat animation */
	{
		m_squatAnimation = std::make_unique<Animation::AnimationInfo>(5);

		uint32_t rightShoulder = Core::AnimationEngine::GetSkeletonBoneIndex("upperarm_r");
		uint32_t leftShoulder = Core::AnimationEngine::GetSkeletonBoneIndex("upperarm_l");
		uint32_t rightCalf = Core::AnimationEngine::GetSkeletonBoneIndex("calf_r");
		uint32_t leftCalf = Core::AnimationEngine::GetSkeletonBoneIndex("calf_l");
		uint32_t rightThigh = Core::AnimationEngine::GetSkeletonBoneIndex("thigh_r");
		uint32_t leftThigh = Core::AnimationEngine::GetSkeletonBoneIndex("thigh_l");
		uint32_t pelivs = Core::AnimationEngine::GetSkeletonBoneIndex("pelvis");
		uint32_t rightFoot = Core::AnimationEngine::GetSkeletonBoneIndex("foot_r");
		uint32_t leftFoot = Core::AnimationEngine::GetSkeletonBoneIndex("foot_l");

		AltMath::Quaternion shoulderRotation = Tools::Math::CreateQuaternionFromEuler(AltMath::Vector3f(0.0f, 0.0f, -80.0f));
		AltMath::Quaternion calfRotation = Tools::Math::CreateQuaternionFromEuler(AltMath::Vector3f(0.0f, 0.0f, -120.0f));
		AltMath::Quaternion thighRotation = Tools::Math::CreateQuaternionFromEuler(AltMath::Vector3f(0.0f, 0.0f, 100.0f));
		AltMath::Quaternion footRotation = Tools::Math::CreateQuaternionFromEuler(AltMath::Vector3f(0.0f, 0.0f, 40.0f));
		AltMath::Quaternion pelvisRotation = Tools::Math::CreateQuaternionFromEuler(AltMath::Vector3f(0.0f, 0.0f, -15.0f));

		AltMath::Vector3f rootTranslation = AltMath::Vector3f(0.0f, 20.0f, -37.5f);

		m_squatAnimation->SetBoneRelativeTransformation(rightShoulder, 1, std::make_pair(AltMath::Vector3f::Zero, shoulderRotation));
		m_squatAnimation->SetBoneRelativeTransformation(leftShoulder, 1, std::make_pair(AltMath::Vector3f::Zero, shoulderRotation));
		m_squatAnimation->SetBoneRelativeTransformation(rightShoulder, 2, std::make_pair(AltMath::Vector3f::Zero, shoulderRotation));
		m_squatAnimation->SetBoneRelativeTransformation(leftShoulder, 3, std::make_pair(AltMath::Vector3f::Zero, shoulderRotation));
		m_squatAnimation->SetBoneRelativeTransformation(rightShoulder, 3, std::make_pair(AltMath::Vector3f::Zero, shoulderRotation));
		m_squatAnimation->SetBoneRelativeTransformation(leftShoulder, 2, std::make_pair(AltMath::Vector3f::Zero, shoulderRotation));
		m_squatAnimation->SetBoneRelativeTransformation(rightCalf, 2, std::make_pair(AltMath::Vector3f::Zero, calfRotation));
		m_squatAnimation->SetBoneRelativeTransformation(leftCalf, 2, std::make_pair(AltMath::Vector3f::Zero, calfRotation));
		m_squatAnimation->SetBoneRelativeTransformation(rightThigh, 2, std::make_pair(AltMath::Vector3f::Zero, thighRotation));
		m_squatAnimation->SetBoneRelativeTransformation(leftThigh, 2, std::make_pair(AltMath::Vector3f::Zero, thighRotation));
		m_squatAnimation->SetBoneRelativeTransformation(pelivs, 2, std::make_pair(AltMath::Vector3f::Zero, pelvisRotation));
		m_squatAnimation->SetBoneRelativeTransformation(0, 2, std::make_pair(rootTranslation, AltMath::Quaternion::Identity()));
		m_squatAnimation->SetBoneRelativeTransformation(rightFoot, 2, std::make_pair(AltMath::Vector3f::Zero, footRotation));
		m_squatAnimation->SetBoneRelativeTransformation(leftFoot, 2, std::make_pair(AltMath::Vector3f::Zero, footRotation));
	}
}

void AnimationProgramming::Simulations::CSimulation::CreateAnimationInstances()
{
	m_walkAnimationInstance = std::make_unique<Animation::AnimationInstance>(*m_walkAnimation);
	m_runAnimationInstance = std::make_unique<Animation::AnimationInstance>(*m_runAnimation);
	m_dabAnimationInstance = std::make_unique<Animation::AnimationInstance>(*m_dabAnimation);
	m_squatAnimationInstance = std::make_unique<Animation::AnimationInstance>(*m_squatAnimation);

	std::string animationConfigFolder = Tools::IniManager::Animation->Get<std::string>("animations_settings_path");

	Tools::IniManager::SetupAnimationInstanceFromIniFile(*m_walkAnimationInstance, animationConfigFolder + "walk_anim.ini");
	Tools::IniManager::SetupAnimationInstanceFromIniFile(*m_runAnimationInstance, animationConfigFolder + "run_anim.ini");
	Tools::IniManager::SetupAnimationInstanceFromIniFile(*m_dabAnimationInstance, animationConfigFolder + "dab_anim.ini");
	Tools::IniManager::SetupAnimationInstanceFromIniFile(*m_squatAnimationInstance, animationConfigFolder + "squat_anim.ini");
}

void AnimationProgramming::Simulations::CSimulation::CreateSkeleton()
{
	m_skeleton.CreateSkeletonFromBindPose();
}

void AnimationProgramming::Simulations::CSimulation::PlayDefaultAnimation()
{
	m_animator.PlayAnimation(*m_walkAnimationInstance);
}

void AnimationProgramming::Simulations::CSimulation::DisplayInputs()
{
	system("CLS");
	std::cout << "############## TIMELINE INPUTS ##############\n";
	std::cout << "#                                           #\n";
	std::cout << "# - [Z][X] navigate between key frames      #\n";
	std::cout << "# - [P] to pause the timeline               #\n";
	std::cout << "# - [R] to toggle rewind effector           #\n";
	std::cout << "# - [L] to toggle ignore looping effector   #\n";
	std::cout << "# - [T] to toggle ignore transitioning eff. #\n";
	std::cout << "# - [I] to toggle frame interpolation eff.  #\n";
	std::cout << "#                                           #\n";
	std::cout << "############# ANIMATION INPUTS ##############\n";
	std::cout << "#                                           #\n";
	std::cout << "# - [N] to speed down the animator          #\n";
	std::cout << "# - [M] to speed up the animator            #\n";
	std::cout << "# - [J] to reset the speed of the animator  #\n";
	std::cout << "#                                           #\n";
	std::cout << "############# RENDERING INPUTS ##############\n";
	std::cout << "#                                           #\n";
	std::cout << "# - [G] to toggle gizmo                     #\n";
	std::cout << "# - [K] to toggle skeleton                  #\n";
	std::cout << "# - [V] to toggle wireframe mode            #\n";
	std::cout << "#                                           #\n";
	std::cout << "############### OTHER INPUTS ################\n";
	std::cout << "#                                           #\n";
	std::cout << "# - [1][2][3][4] to change animation        #\n";
	std::cout << "# - [5] to play bind pose (T-Pose)          #\n";
	std::cout << "# - [F] to print the framerate in console   #\n";
	std::cout << "# - [H] to re-print the input list          #\n";
	std::cout << "#                                           #\n";
	std::cout << "#############################################\n";
}

void AnimationProgramming::Simulations::CSimulation::Update(float p_deltaTime)
{
	CheckInputs(p_deltaTime);
	UpdateAnimators(p_deltaTime);
	DrawScene();
}

void AnimationProgramming::Simulations::CSimulation::CheckInputs(float p_deltaTime)
{
	m_inputManager.Update();

	if (m_inputManager.IsKeyEventOccured('1'))
		m_animator.PlayAnimation(*m_walkAnimationInstance);

	if (m_inputManager.IsKeyEventOccured('2'))
		m_animator.PlayAnimation(*m_runAnimationInstance);

	if (m_inputManager.IsKeyEventOccured('3'))
		m_animator.PlayAnimation(*m_dabAnimationInstance);

	if (m_inputManager.IsKeyEventOccured('4'))
		m_animator.PlayAnimation(*m_squatAnimationInstance);

	if (m_inputManager.IsKeyEventOccured('5'))
		m_animator.StopAnimation();

	if (m_inputManager.IsKeyEventOccured('I'))
		m_animator.GetTimeline().ToggleEffector(Animation::ETimelineEffector::IGNORE_FRAME_INTERPOLATION);

	if (m_inputManager.IsKeyEventOccured('P'))
		m_animator.GetTimeline().TogglePause();

	if (m_inputManager.IsKeyEventOccured('R'))
		m_animator.GetTimeline().ToggleEffector(Animation::ETimelineEffector::REWIND);

	if (m_inputManager.IsKeyEventOccured('L'))
	{
		m_animator.GetTimeline().ToggleEffector(Animation::ETimelineEffector::IGNORE_LOOPING);
		m_animator.GetTimeline().Play();
	}

	if (m_inputManager.IsKeyEventOccured('T'))
		m_animator.GetTimeline().ToggleEffector(Animation::ETimelineEffector::IGNORE_TRANSITIONING);

	if (m_inputManager.IsKeyEventOccured('N') && m_animator.GetGlobalSpeedCoefficient() > 0.1f)
		m_animator.SetGlobalSpeedCoefficient(std::max<float>(m_animator.GetGlobalSpeedCoefficient() * 0.75f, 0.1f));

	if (m_inputManager.IsKeyEventOccured('M') && m_animator.GetGlobalSpeedCoefficient() < 10.0f)
		m_animator.SetGlobalSpeedCoefficient(std::min<float>(m_animator.GetGlobalSpeedCoefficient() * 1.5f, 10.0f));

	if (m_inputManager.IsKeyEventOccured('J'))
		m_animator.SetGlobalSpeedCoefficient(1.0f);

	if (m_inputManager.IsKeyEventOccured('G'))
		Tools::IniManager::Rendering->Set<bool>("show_gizmo", !Tools::IniManager::Rendering->Get<bool>("show_gizmo"));

	if (m_inputManager.IsKeyEventOccured('K'))
		Tools::IniManager::Rendering->Set<bool>("show_skeleton", !Tools::IniManager::Rendering->Get<bool>("show_skeleton"));

	if (m_inputManager.IsKeyEventOccured('V'))
		ToggleWireframe();

	if (m_inputManager.IsKeyEventOccured('F'))
		PrintFramerate(p_deltaTime);

	if (m_inputManager.IsKeyEventOccured('H'))
		DisplayInputs();

	if (m_inputManager.IsKeyEventOccured('X'))
	{
		m_animator.GetTimeline().Pause();
		m_animator.GetTimeline().GoToNextKeyFrame(true);
	}

	if (m_inputManager.IsKeyEventOccured('Z'))
	{
		m_animator.GetTimeline().Pause();
		m_animator.GetTimeline().GoToPreviousKeyFrame(true);
	}
}

void AnimationProgramming::Simulations::CSimulation::UpdateAnimators(float p_deltaTime)
{
	m_animator.Update(p_deltaTime);
}

void AnimationProgramming::Simulations::CSimulation::DrawScene()
{
	if (Tools::IniManager::Rendering->Get<bool>("show_grid"))
		Rendering::Renderer::DrawGrid();

	if (Tools::IniManager::Rendering->Get<bool>("show_gizmo"))
		Rendering::Renderer::DrawGizmo(Data::Color::Red, Data::Color::Green, Data::Color::Blue, Tools::IniManager::Rendering->Get<float>("gizmo_size"));

	if (Tools::IniManager::Rendering->Get<bool>("show_skeleton"))
		m_skeletonDrawer.Draw(m_skeleton, AltMath::Vector3f::Zero);

	if (Tools::IniManager::Rendering->Get<bool>("show_timeline") && m_animator.HasAnimation())
		m_timelineDrawer.Draw(m_animator.GetTimeline(), AltMath::Vector3f(0.0f, 0.0, 225.0f));

	/* Modify line thickness for next draw calls (Wireframe mode for instance) */
	Rendering::Renderer::SetLineThickness(Tools::IniManager::Rendering->Get<float>("line_thickness"));
}

void AnimationProgramming::Simulations::CSimulation::ToggleWireframe()
{
	Rendering::Renderer::SetDrawMode(Rendering::Renderer::GetDrawMode() == Rendering::EDrawMode::WIREFRAME ? Rendering::EDrawMode::NORMAL : Rendering::EDrawMode::WIREFRAME);
}

void AnimationProgramming::Simulations::CSimulation::PrintFramerate(float p_deltaTime)
{
	std::cout << "Actual Framerate: " << 1.0f / p_deltaTime << " FPS" << std::endl;
}

void AnimationProgramming::Simulations::CSimulation::PrintHelpTip()
{
	std::cout << "Press [H] to display inputs in the console" << std::endl;
}
