#include "Akkad/PlatformMacros.h"
#include "IWindow.h"
#include "Event.h"
#include "Akkad/Graphics/ImGuiHandler.h"
#include "Akkad/Graphics/RenderCommand.h"
#include "Akkad/Graphics/RenderContext.h"
#include "Layer.h"

namespace Akkad {
	using namespace Graphics;
	class Application {
	public:
		static Application& GetInstance() { return s_Instance; }

		static void AttachLayer(Layer* layer) { GetInstance().AttachLayerImpl(layer); }
		static void DetachLayer(Layer* layer) { GetInstance().DetachLayerImpl(layer); }
		static void Run() { GetInstance().RunImpl(); }
		static void Init() { GetInstance().InitImpl(); }
		static void Shutdown() { GetInstance().m_Running = false; };
		static SharedPtr<RenderPlatform> GetRenderPlatform() { return GetInstance().m_platform; }
		Window* GetWindow() { return m_Window; }
		
	private:
		friend class Window;
		Application() {}
		~Application();
		static Application s_Instance;

		void InitImpl();
		void RunImpl();
		bool m_Running = false;

		// -------- Event Handlers -----------------
		void OnEvent(Event& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnWindowClose(WindowCloseEvent& e);
		// -------------------------------------

		// -------- Layer Handlers ------------------
		void AttachLayerImpl(Layer* layer) {
			m_Layers.push_back(layer);
		}

		void DetachLayerImpl(Layer* layer) {
			m_Layers.erase(std::remove(m_Layers.begin(), m_Layers.end(), layer), m_Layers.end());
			delete layer;
		}
		// -----------------------------------------

		std::vector<Layer*> m_Layers;

		Window* m_Window = nullptr;

		SharedPtr<ImGuiHandler> m_ImguiHandler;
		SharedPtr<RenderPlatform> m_platform;
		

	};
}