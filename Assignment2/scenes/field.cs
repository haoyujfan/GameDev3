using Godot;
using System;

public partial class field : Node3D
{
	//var player = new Player();
	//private Player player;
	private RichTextLabel Points;
	// Called when the node enters the scene tree for the first time.
	public override void _Ready()
	{
		//player = GetNode<Player>("Player");
		GetNode<RichTextLabel>("Points");
	}

	// Called every frame. 'delta' is the elapsed time since the previous frame.
	public override void _Process(double delta)
	{
		//Points.Text = "Points: " + player.Call(Player.get_points());
		//Points.Text = "Points: " + GetNode<Player>("Player").get_points();
	}
}
