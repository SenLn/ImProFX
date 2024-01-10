// improfx2_demo.
#include "improfx2_demo.h"

using namespace std;
using namespace ProFxFramework;

const string AboutText = 
u8R"(ImProFX Framework
����ImGui��OpenGL4.6
����������GUI���
ʹ����ɫ�������ԭ��
���Ӿ�Ч��,�Լ��ṩ��
����������ϵͳ��
�̳߳ء�����ȿ�������.

��ѧϰ�߿�����,һ��GUI
�����Ҫ�ǳ�����ʱ��
��ĥ,���Խ����Ҫ����
���汾�ͼܹ��ĵ���...

- RCSZ 2024.01.10)";

const char* vArch[8][2] = {
	{ "1.0 Alpha", "EA-OGL" },
	{ "1.1 Alpah", "EA-OGL" },
	{ "2.0 Test1", "ST-OGL" },
	{ "2.0 Test2", "ST-OGL" },
	{ "2.0 Alpha", "ST-OGL" },
	{ "2.1 Alpha", "ST-OGL" },
    { "2.2 *ImFX", "ST-IMFXGL" },
	{ "2.2 Alpha", "ST-IMFXGL" }
};

bool ImprofxDemoClass22::LogicInitialization(FRMCORE_PACKAGE& FrmDat) {

	SecWindowIcon.push_back(FrmCore.FindRawTextureImg(FrmDat.DataTextureRaw, "icon_settings"));
	SecWindowIcon.push_back(FrmCore.FindRawTextureImg(FrmDat.DataTextureRaw, "icon_arch"));
	SecWindowIcon.push_back(FrmCore.FindRawTextureImg(FrmDat.DataTextureRaw, "icon_info"));

	DemoMainPage.push_back(FrmCore.FindRawTextureImg(FrmDat.DataTextureRaw, "demo2a_main"));
	DemoMainPage.push_back(FrmCore.FindRawTextureImg(FrmDat.DataTextureRaw, "demo2a_arch"));
	DemoMainPage.push_back(FrmCore.FindRawTextureImg(FrmDat.DataTextureRaw, "demo2a_core"));
	DemoMainPage.push_back(FrmCore.FindRawTextureImg(FrmDat.DataTextureRaw, "demo2a_next"));

	DemoMainPageIcon.push_back(FrmCore.FindRawTextureImg(FrmDat.DataTextureRaw, "demo2a_icon_shfx"));
	DemoMainPageIcon.push_back(FrmCore.FindRawTextureImg(FrmDat.DataTextureRaw, "demo2a_icon_anim"));
	DemoMainPageIcon.push_back(FrmCore.FindRawTextureImg(FrmDat.DataTextureRaw, "demo2a_icon_ptcs"));
	DemoMainPageIcon.push_back(FrmCore.FindRawTextureImg(FrmDat.DataTextureRaw, "demo2a_icon_tool"));

	ArchImage = FrmCore.FindRawTextureImg(FrmDat.DataTextureRaw, "demo2a_arch_img");

	FrmStatic.StaticParticleSysAlloc(FrmDat.ParticleSystem, "DemoParticleSys", Vector2T<float>(1680.0f, 945.0f));

	ConfigAnimation(FrmDat);
	
	return true; // ����demo���÷�����.
}

void ImprofxDemoClass22::SecondaryWindow(FRMCORE_PACKAGE& FrmDat, FRMCORE_INFO& FrmInfo) {
	// ������.
	FrmInfo.ImProFXGUI->SetCursorPos(ImVec2(IMGUI_ITEM_SPC, IMGUI_ITEM_SPC + WindowPageYpos.vector_y));
	// �Ӵ���.
	FrmInfo.ImProFXGUI->ImGuiWindowChild("AttachWindow",
		[&]() {
			FrmInfo.ImProFXGUI->SetCursorPosX(IMGUI_ITEM_SPC / 2.0f);
			FrmInfo.ImProFXGUI->Image(CVT_IMPTR(FrmCore.FindRawTextureImg(FrmDat.DataTextureRaw, "improfx2_logo")), ImVec2(88.0f, 88.0f));
			FrmInfo.ImProFXGUI->Text("");

			FrmInfo.ImProFXGUI->SetCursorPosX(IMGUI_ITEM_SPC - 2.0f);
			if (ImGuiProAnim::CallAnimButtonImage("img1", FrmDat.DataAnimation, "SecWinButA", FrmCore.FindRawTextureImg(FrmDat.DataTextureRaw, "icon_settings"))) {
				SecWindowFlags.vector_x = !SecWindowFlags.vector_x;
				SecWindowFlags.vector_y = false;
				SecWindowFlags.vector_z = false;
			}

			FrmInfo.ImProFXGUI->SetCursorPosX(IMGUI_ITEM_SPC - 2.0f);
			if (ImGuiProAnim::CallAnimButtonImage("img2", FrmDat.DataAnimation, "SecWinButB", FrmCore.FindRawTextureImg(FrmDat.DataTextureRaw, "icon_arch"))) {
				SecWindowFlags.vector_y = !SecWindowFlags.vector_y;
				SecWindowFlags.vector_x = false;
				SecWindowFlags.vector_z = false;
			}

			FrmInfo.ImProFXGUI->SetCursorPosX(IMGUI_ITEM_SPC - 2.0f);
			if (ImGuiProAnim::CallAnimButtonImage("img3", FrmDat.DataAnimation, "SecWinButC", FrmCore.FindRawTextureImg(FrmDat.DataTextureRaw, "icon_info"))) {
				SecWindowFlags.vector_z = !SecWindowFlags.vector_z;
				SecWindowFlags.vector_x = false;
				SecWindowFlags.vector_y = false;
			}

			if (!SecWindowFlags.vector_z)
				AboutTextAnim = 0.0f;

			ImGuiProAnim::CallAnimFixedWindow("Settings", FrmDat.DataAnimation, "WindowA", SecWindowFlags.vector_x,
				[&]() {
					FrmInfo.ImProFXGUI->PRO_InterSliderFloat(u8"��������", SettingsBgColor, ImVec2(0.5f, 1.5f), 0.42f);
					FrmInfo.ImProFXGUI->PRO_InterSliderFloat(u8"�����ٶ�", SettingsBgSpeed, ImVec2(0.5f, 1.5f), 0.42f);

					FrmCore.FindSetRenderItemParam(FrmDat.DataShaderFx, "fx_background_shader", "brightness", SettingsBgColor.vector_y);
					FrmCore.FindSetRenderItemParam(FrmDat.DataShaderFx, "fx_background_shader", "speed", SettingsBgSpeed.vector_y);

					FrmInfo.ImProFXGUI->PRO_EndEnterLine();
					FrmInfo.ImProFXGUI->Text(u8"����֡��(FPS): %.2f", FrmInfo.ImProFXGUI->GetImGuiIO().Framerate);

					// "ImGui::GetFrameCount()" Ŀǰ��û�з�װ.
					FrmInfo.ImProFXGUI->Text(u8"��Ⱦ֡��: %d", ImGui::GetFrameCount());

					FrmInfo.ImProFXGUI->Text(u8"�������: %.0f, %.0f", FrmInfo.ImProFXGUI->GetMousePos().x, FrmInfo.ImProFXGUI->GetMousePos().y);

					if (FrmInfo.ImProFXGUI->Button("PageReturn") && WindowPageYpos.vector_x > 937.0f)
						WindowPageYpos.vector_x -= 945.0f;
				},
				ImGuiWindowFlags_NoScrollbar
			);

			ImGuiProAnim::CallAnimFixedWindow("Architecture", FrmDat.DataAnimation, "WindowB", SecWindowFlags.vector_y,
				[&]() {
					FrmInfo.ImProFXGUI->Text("Base: IMPROFX-");
					/*
					* ����װĿǰ��δ��������ʹ��ImGui����.
					* ImProFX 2.2.0 ALPHA.
					*/
					if (ImGui::BeginTable(u8"��ʷ�ܹ�", 2, ImGuiTableFlags_Borders)) {
						// ��ͷ.
						ImGui::TableSetupColumn(u8"�汾", ImGuiTableColumnFlags_WidthFixed, 128.0f);
						ImGui::TableSetupColumn(u8"�ܹ�");
						ImGui::TableHeadersRow();

						for (int row = 0; row < 8; ++row) {
							ImGui::TableNextRow();
							for (int col = 0; col < 2; ++col) {
								ImGui::TableSetColumnIndex(col);
								ImGui::Text(vArch[row][col], row, col);
							}
						}
						ImGui::EndTable();
					}
					FrmInfo.ImProFXGUI->Text("RCSZ. 2024 - 2025.");
				},
				ImGuiWindowFlags_NoScrollbar
			);

			ImGuiProAnim::CallAnimFixedWindow("About", FrmDat.DataAnimation, "WindowC", SecWindowFlags.vector_z,
				[&]() {
					FrmInfo.ImProFXGUI->PRO_ViewTextMultilineAnim("#A3F7B2D8", AboutText, AboutTextAnim, SecWindowFlags.vector_z, ImVec2(240.0f, 342.0f), 1.8f);
				},
				ImGuiWindowFlags_NoScrollbar
			);
		},
		ImVec2(104.0f, 945.0f - IMGUI_ITEM_SPC * 2.0f)
	);
	FrmInfo.ImProFXGUI->SetCursorPos(ImVec2(IMGUI_ITEM_SPC, IMGUI_ITEM_SPC));
}

bool ImprofxDemoClass22::LogicEventLoop(FRMCORE_PACKAGE& FrmDat, FRMCORE_INFO& FrmInfo) {
	
	FrmInfo.ImProFXGUI->PushStyleColor(ImGuiCol_TitleBg, ImVec4(1.0f, 0.32f, 0.0f, 0.52f));
	FrmInfo.ImProFXGUI->PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(1.0f, 0.32f, 0.0f, 0.52f));
	FrmInfo.ImProFXGUI->PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.32f));

	FrmInfo.ImProFXGUI->SetNextWindowPos(ImVec2(0, 0));
	FrmInfo.ImProFXGUI->SetNextWindowSize(FrmInfo.ImProFXGUI->GetImGuiIO().DisplaySize);

	// �ޱ�����, �̶�λ��, �̶���С, �޷��۵�, ���ػ���, �������������¼�.
	ImGuiWindowFlags TmpFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
	FrmInfo.ImProFXGUI->ImGuiWindow("2.0 ALPHA", 
		[&]() {
			FrmInfo.ImProFXGUI->PopStyleColor(3);

			// ��ҳ��.
			ImGui::SetCursorPos(ImVec2(FrmInfo.ImProFXGUI->PRO_ItemCalcCentered(1560.0f) + 50.0f + IMGUI_ITEM_SPC, IMGUI_ITEM_SPC));
			FrmInfo.ImProFXGUI->PRORZ_TemplatePageLSA("MemoMainPage", ImVec2(1560.0f, 877.5f), DemoMainPage, DemoMainPagePlayflags, DemoMainPageXpos, false);

			FrmInfo.ImProFXGUI->SetCursorPosX(FrmInfo.ImProFXGUI->PRO_ItemCalcCentered(768.0f + IMGUI_ITEM_SPC) + 50.0f + IMGUI_ITEM_SPC);
			DemoMainPagePlayflags.vector_x = ImGuiProAnim::CallAnimButton("PreviousPage", FrmDat.DataAnimation, "PalyButA");
			FrmInfo.ImProFXGUI->SameLine();
			DemoMainPagePlayflags.vector_y = ImGuiProAnim::CallAnimButton("NextPage", FrmDat.DataAnimation, "PlayButB");

			size_t PageCount = size_t(DemoMainPageXpos.vector_x / 1560.0f);

			ImGuiProAnimNodes::CallAnimNodesVector(PageCount, FrmDat.DataAnimationNodes, "NodesArch",
				NODESFUNC{
					FrmInfo.ImProFXGUI->Image(
						CVT_IMPTR(ArchImage),
						ImVec2(size.vector_x, size.vector_y),
						ImVec2(0.0f, 0.0f),
						ImVec2(1.0f, 1.0f),
						ImVec4(color.vector_x, color.vector_y, color.vector_z, color.vector_w)
					);
				}
			);

			ImGuiProAnimNodes::CallAnimNodesVector(PageCount, FrmDat.DataAnimationNodes, "NodesIcon1", NODESFUNC{
					FrmInfo.ImProFXGUI->Image(
						CVT_IMPTR(DemoMainPageIcon[0]),
						ImVec2(size.vector_x, size.vector_y),
						ImVec2(0.0f, 0.0f),
						ImVec2(1.0f, 1.0f),
						ImVec4(color.vector_x, color.vector_y, color.vector_z, color.vector_w)
					);
				}
			);
			ImGuiProAnimNodes::CallAnimNodesVector(PageCount, FrmDat.DataAnimationNodes, "NodesIcon2", NODESFUNC{
					FrmInfo.ImProFXGUI->Image(
						CVT_IMPTR(DemoMainPageIcon[1]),
						ImVec2(size.vector_x, size.vector_y),
						ImVec2(0.0f, 0.0f),
						ImVec2(1.0f, 1.0f),
						ImVec4(color.vector_x, color.vector_y, color.vector_z, color.vector_w)
					);
				}
			);
			ImGuiProAnimNodes::CallAnimNodesVector(PageCount, FrmDat.DataAnimationNodes, "NodesIcon3", NODESFUNC{
					FrmInfo.ImProFXGUI->Image(
						CVT_IMPTR(DemoMainPageIcon[2]),
						ImVec2(size.vector_x, size.vector_y),
						ImVec2(0.0f, 0.0f),
						ImVec2(1.0f, 1.0f),
						ImVec4(color.vector_x, color.vector_y, color.vector_z, color.vector_w)
					);
				}
			);
			ImGuiProAnimNodes::CallAnimNodesVector(PageCount, FrmDat.DataAnimationNodes, "NodesIcon4", NODESFUNC{
					FrmInfo.ImProFXGUI->Image(
						CVT_IMPTR(DemoMainPageIcon[3]),
						ImVec2(size.vector_x, size.vector_y),
						ImVec2(0.0f, 0.0f),
						ImVec2(1.0f, 1.0f),
						ImVec4(color.vector_x, color.vector_y, color.vector_z, color.vector_w)
					);
				}
			);

			ImGuiProAnimNodes::CallAnimNodesVector(PageCount, FrmDat.DataAnimationNodes, "NodesNext", NODESFUNC{
					FrmInfo.ImProFXGUI->Image(
						CVT_IMPTR(FrmCore.FindRawTextureImg(FrmDat.DataTextureRaw, "demo2a_button_next")),
						ImVec2(size.vector_x, size.vector_y),
						ImVec2(0.0f, 0.0f),
						ImVec2(1.0f, 1.0f),
						ImVec4(color.vector_x, color.vector_y, color.vector_z, color.vector_w)
					);
					if (FrmInfo.ImProFXGUI->IsItemHovered(ImGuiHoveredFlags_AllowWhenOverlapped) && FrmInfo.ImProFXGUI->IsMouseDown(0))
						WindowPageYpos.vector_x += 945.0f;
				}
			);

			FrmInfo.ImProFXGUI->PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.32f, 0.0f, 0.92f));
			FrmInfo.ImProFXGUI->PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.55f, 0.0f, 1.0f, 0.32f));

			FrmInfo.ImProFXGUI->SetCursorPos(ImVec2(110.0f, ImGui::GetCursorPos().y + 4.0f));
			FrmInfo.ImProFXGUI->ImGuiWindowChild("NextPage1",
				[&]() {
					FrmInfo.ImProFXGUI->SetNextItemWidth(372.0f);
					FrmInfo.ImProFXGUI->InputFloat(InputFloat2, u8"������������ֲ�", ParticleConfigLife.data(), 0.0f, 0.0f, "%.2f");

					FrmInfo.ImProFXGUI->SetNextItemWidth(372.0f);
					FrmInfo.ImProFXGUI->InputFloat(InputFloat2, u8"����λ������ֲ�", ParticleConfigPosition.data(), 0.0f, 0.0f, "%.2f");

					FrmInfo.ImProFXGUI->SetNextItemWidth(372.0f);
					FrmInfo.ImProFXGUI->InputFloat(InputFloat2, u8"������������ֲ�", ParticleConfigVector.data(), 0.0f, 0.0f, "%.2f");

					FrmInfo.ImProFXGUI->SetNextItemWidth(240.0f);
					FrmInfo.ImProFXGUI->InputFloat(InputFloat1, u8"��������", &ParticleNumber);

					FrmInfo.ImProFXGUI->SameLine();
					FrmInfo.ImProFXGUI->PRO_CheckboxTriangle("R", &ParticleConfigColorSys.vector_x);

					FrmInfo.ImProFXGUI->SameLine();
					FrmInfo.ImProFXGUI->PRO_CheckboxTriangle("G", &ParticleConfigColorSys.vector_y);

					FrmInfo.ImProFXGUI->SameLine();
					FrmInfo.ImProFXGUI->PRO_CheckboxTriangle("B", &ParticleConfigColorSys.vector_z);

					if (FrmInfo.ImProFXGUI->RadioButton(u8"��ɢģʽ: ����", ParticleMode == 1 << 1)) ParticleMode = 1 << 1;
					if (FrmInfo.ImProFXGUI->RadioButton(u8"��ɢģʽ: Բ����ɢ[����]", ParticleMode == 1 << 2)) ParticleMode = 1 << 2;
					if (FrmInfo.ImProFXGUI->RadioButton(u8"��ɢģʽ: ������ɢ[����]", ParticleMode == 1 << 3)) ParticleMode = 1 << 3;
					if (FrmInfo.ImProFXGUI->RadioButton(u8"��ɢģʽ: Ʈ����ɢ[����]", ParticleMode == 1 << 4)) ParticleMode = 1 << 4;

					auto TempPtcObj = FrmStatic.StaticParticleSysFind(FrmDat.ParticleSystem, "DemoParticleSys");
					TempPtcObj->ParticleSystemUpdate();

					if (ImGuiProAnim::CallAnimButton(u8"��������", FrmDat.DataAnimation, "PlayButPTC")) {

						ImParticle::ImPTCgenerator GenParticles;

						GenParticles.ConfigCreateMode((ParticleCreateMode)ParticleMode);
						GenParticles.ConfigCreateNumber(ParticleNumber);
						GenParticles.ConfigLifeDispersion(ParticleConfigLife);
						GenParticles.ConfigRandomDispersion(ParticleConfigVector, ParticleConfigPosition, ParticleConfigColorSys);

						TempPtcObj->ParticleCreate(&GenParticles);
					}

					if (ImGuiProAnim::CallAnimButton("NextPage", FrmDat.DataAnimation, "PlayButNEXT"))
						WindowPageYpos.vector_x += 945.0f;

					FrmInfo.ImProFXGUI->SetCursorPos(ImVec2(528.0f, IMGUI_ITEM_SPC));
					FrmInfo.ImProFXGUI->Image(
						CVT_IMPTR(TempPtcObj->GetParticleRenderHandle()),
						ImVec2(1024.0f, 576.0f),
						ImVec2(0.0f, 0.0f),
						ImVec2(1.0f, 1.0f),
						ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
						ImVec4(0.55f, 0.0f, 1.0f, 0.85f)
					);

					FrmInfo.ImProFXGUI->ImGuiWindowChild("LogView",
						[&]() {
							FrmInfo.ImProFXGUI->PRO_SmoothYSlide(NextPageYpos);

							// "ImGui::SetWindowFontScale"��δ��װ.
							ImGui::SetWindowFontScale(0.872f);

							ImVec4 color = ImVec4();
							for (const auto& logstr : LOGCONS::ReadLogCache::ExtractLogSegment(128)) {

								switch (logstr.LogLabel) {
								case(LOG_INFO): { color = ImVec4(1.0f, 1.0f, 1.0f, 0.72f);  break; };
								case(LOG_ERROR): { color = ImVec4(1.0f, 0.0f, 0.0f, 0.72f);  break; };
								case(LOG_WARNING): { color = ImVec4(1.0f, 1.0f, 0.0f, 0.72f);  break; };
								case(LOG_TRACE): { color = ImVec4(0.0f, 1.0f, 1.0f, 0.72f);  break; };
								case(LOG_PERF): { color = ImVec4(0.78f, 0.0f, 1.0f, 0.72f); break; };
								}
								FrmInfo.ImProFXGUI->TextColored(color, logstr.LogString.c_str());
							}
						},
						ImVec2(1544.0f, 328.0f), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse
					);
				},
				ImVec2(1560.0f, 945.0f), true
			);

			FrmInfo.ImProFXGUI->PopStyleColor(2);

			FrmInfo.ImProFXGUI->SetCursorPosX(110.0f);
			FrmInfo.ImProFXGUI->ImGuiWindowChild("NextPage2",
				[&]() {
					FrmInfo.ImProFXGUI->Image(CVT_IMPTR(FrmCore.FindRenderItemFBO(FrmDat.DataShaderFx, "fx_circle_shader")), ImVec2(768.0f, 432.0f));
					FrmInfo.ImProFXGUI->SameLine();
					FrmInfo.ImProFXGUI->Image(CVT_IMPTR(FrmCore.FindRenderItemFBO(FrmDat.DataShaderFx, "fx_hexerino_shader")), ImVec2(768.0f, 432.0f));

					FrmInfo.ImProFXGUI->PRO_EndEnterLine();
					ImVec2 temp_curpos = FrmInfo.ImProFXGUI->GetCursorPos();

					FrmInfo.ImProFXGUI->PRO_TextTitleP1("Hello World! P1", 384.0f);
					FrmInfo.ImProFXGUI->PRO_TextTitleP2("Hello World! P2", 384.0f);
					FrmInfo.ImProFXGUI->PRO_TextTitleP3("Hello World! P3", 384.0f);
					FrmInfo.ImProFXGUI->TextColored(ImVec4(1.0, 1.0, 1.0, 1.0), "Hello World!");

#define NULLFUNC [](){}
					FrmInfo.ImProFXGUI->SetCursorPos(ImVec2(384.0f - IMGUI_ITEM_SPC * 3.0f, temp_curpos.y));
					FrmInfo.ImProFXGUI->PRORZ_TemplatePageLayout169A("DemoT1", NULLFUNC, NULLFUNC, NULLFUNC, NULLFUNC, 0.5f);

					FrmInfo.ImProFXGUI->SameLine();
					FrmInfo.ImProFXGUI->PRORZ_TemplatePageLayout169B("DemoT2", NULLFUNC, NULLFUNC, NULLFUNC, NULLFUNC, 0.5f);

					FrmInfo.ImProFXGUI->SameLine();
					FrmInfo.ImProFXGUI->PRORZ_TemplatePageLayout1216A("DemoT3", NULLFUNC, NULLFUNC, NULLFUNC, 0.5f);
				},
				ImVec2(1560.0f, 945.0f), true
			);

			SecondaryWindow(FrmDat, FrmInfo);
			FrmInfo.ImProFXGUI->PRO_SmoothYSlide(WindowPageYpos, 0.42f, false, false);
		}, 
		nullptr, TmpFlags
	);
	return true;
}

void ImprofxDemoClass22::LogicCloseFree() {
	
}