#pragma once

#include "halley/core/api/halley_api_internal.h"
#include <SDL2/SDL.h>

namespace Halley
{
	class SDLWindow;

	class SystemSDL final : public SystemAPIInternal
	{
	public:
		explicit SystemSDL(Maybe<String> saveCryptKey);

	protected:
		void init() override;
		void deInit() override;

		Path getAssetsPath(const Path& gamePath) const override;
		Path getUnpackedAssetsPath(const Path& gamePath) const override;

		bool generateEvents(VideoAPI* video, InputAPI* input) override;

		std::unique_ptr<ResourceDataReader> getDataReader(String path, int64_t start, int64_t end) override;

		std::shared_ptr<Window> createWindow(const WindowDefinition& window) override;
		void destroyWindow(std::shared_ptr<Window> window) override;

		Vector2i getScreenSize(int n) const override;
		Rect4i getDisplayRect(int screen) const override;
		Vector2i getCenteredWindow(Vector2i size, int screen) const;
		std::unique_ptr<GLContext> createGLContext() override;

		void showCursor(bool show) override;

		std::shared_ptr<ISaveData> getStorageContainer(SaveDataType type, const String& containerName) override;

		void setEnvironment(Environment* env) override;

		bool canExit() override;

		std::shared_ptr<IClipboard> getClipboard() const override;

		void setThreadName(const String& name) override;

	private:
		void processVideoEvent(VideoAPI* video, const SDL_Event& event);

		void printDebugInfo() const;

		void initVideo() const;
		void deInitVideo();

	private:
		std::vector<std::shared_ptr<SDLWindow>> windows;
		mutable bool videoInit = false;
		std::map<SaveDataType, Path> saveDir;
		std::shared_ptr<IClipboard> clipboard;
		Maybe<String> saveCryptKey;
	};
}
