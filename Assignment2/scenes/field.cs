using Godot;
using System;

public partial class field : Node3D
{
	//var player = new Player();
	//private Player player;
	private RichTextLabel Points;
	private int points_value;
	// Called when the node enters the scene tree for the first time.
	public override void _Ready()
	{
		//player = GetNode<Player>("Player");
		Points = GetNode<RichTextLabel>("Points");
		points_value = 0;
	}

	// Called every frame. 'delta' is the elapsed time since the previous frame.
	public override void _Process(double delta)
	{
		//Points.Text = "Points: " + player.Call(Player.get_points());
		//Points.Text = "Points: " + GetNode<Player>("Player").get_points();
		Points.Text = "Points: " + points_value.ToString();
	}
	
	private void _on_player_interact_orange()
	{
		points_value++;
	}
	
	private void _on_cactus_interact_cactus()
	{
		points_value--;
	}
}
