using Godot;
using System;

public partial class field : Node3D
{
	private Player MyPlayer;
	private RichTextLabel Points;
	// Called when the node enters the scene tree for the first time.
	public override void _Ready()
	{
		MyPlayer = GetNode<Player>("Player/Player");
		Points = GetNode<RichTextLabel>("Points");
	}

	// Called every frame. 'delta' is the elapsed time since the previous frame.
	public override void _Process(double delta)
	{
		Points.Text = "Points: " + MyPlayer.get_points();
	}
}
