#pragma once
#include "api/halley_api_internal.h"

namespace Halley {
	class DummySystemAPI : public SystemAPIInternal {
	public:
		std::unique_ptr<ResourceDataReader> getDataReader(String path, int64_t start, int64_t end) override;
		std::unique_ptr<ResourceDataReader> getDataReader(gsl::span<const gsl::byte> memory) override;
		std::unique_ptr<GLContext> createGLContext() override;
		std::shared_ptr<Window> createWindow(const WindowDefinition& window) override;
		void destroyWindow(std::shared_ptr<Window> window) override;
		Vector2i getScreenSize(int n) const override;
		Rect4i getDisplayRect(int screen) const override;
		void showCursor(bool show) override;
		bool generateEvents(VideoAPI* video, InputAPI* input) override;
		void init() override;
		void deInit() override;
	};

	class DummyWindow : public Window
	{
	public:
		explicit DummyWindow(const WindowDefinition& definition);

		void update(const WindowDefinition& definition) override;
		void show() override;
		void hide() override;
		void setVsync(bool vsync) override;
		void swap() override;
		Rect4i getWindowRect() const override;
		const WindowDefinition& getDefinition() const override;

	private:
		const WindowDefinition& definition;
	};
}