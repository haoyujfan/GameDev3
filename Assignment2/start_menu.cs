using Godot;
using System;

public partial class start_menu : Node2D
{
	private void _on_start_pressed()
	{
		GetTree().ChangeSceneToFile("res://scenes/lose_screen.tscn");
	}
	
	private void _on_exit_pressed()
	{
		GetTree().Quit();
	}
}
