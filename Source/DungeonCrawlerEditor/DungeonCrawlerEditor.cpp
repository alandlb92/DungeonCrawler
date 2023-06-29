#include "DungeonCrawlerEditor.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"
#include "Components/AttackComponent.h"

IMPLEMENT_GAME_MODULE(FDungeonCrawlerEditorModule, DungeonCrawlerEditor);

void FDungeonCrawlerEditorModule::StartupModule()
{
    // Check if editor is valid
    if (GUnrealEd)
    {
        // Registerin the move visualizer
        TSharedPtr<FCharacterEnemyVisualizer> EnemyCharVisualizer = MakeShareable(new FCharacterEnemyVisualizer);
        if (EnemyCharVisualizer.IsValid())
        {
            GUnrealEd->RegisterComponentVisualizer(UAttackComponent::StaticClass()->GetFName(), EnemyCharVisualizer);
            EnemyCharVisualizer->OnRegister();
        }
    }
}

void FDungeonCrawlerEditorModule::ShutdownModule()
{
    // Check if editor is valid
    if (GUnrealEd)
    {
        GUnrealEd->UnregisterComponentVisualizer(UAttackComponent::StaticClass()->GetFName());
    }
}