#include "DungeonCrawlerEditor.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"

IMPLEMENT_GAME_MODULE(FDungeonCrawlerEditorModule, DungeonCrawlerEditor);

//void FDungeonCrawlerEditorModule::StartupModule()
//{
//    // Check if editor is valid
//    if (GUnrealEd)
//    {
//        // Registerin the move visualizer
//        TSharedPtr<FMoveComponentVisualizer> MoveVisualizer = MakeShareable(new FMoveComponentVisualizer);
//        if (MoveVisualizer.IsValid())
//        {
//            GUnrealEd->RegisterComponentVisualizer(UMoveComponent::StaticClass()->GetFName(), MoveVisualizer);
//            MoveVisualizer->OnRegister();
//        }
//    }
//}
//
//void FDungeonCrawlerEditorModule::ShutdownModule()
//{
//    // Check if editor is valid
//    if (GUnrealEd)
//    {
//        GUnrealEd->UnregisterComponentVisualizer(UMoveComponent::StaticClass()->GetFName());
//    }
//}