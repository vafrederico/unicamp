<?php 
	if(!isset($_SESSION)){
		session_start();
	}
	unset($_SESSION['usuario']);
header('Location: index.php');
?>