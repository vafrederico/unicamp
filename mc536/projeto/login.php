<?php 
	if(!isset($_SESSION)){
		session_start();
	}
	if(isset($_SESSION['usuario']) && $_SESSION['usuario'] != -1)
		header('Location: index.php');

	require("phar://neo4jphp.phar");
	use Everyman\Neo4j\Client,
        Everyman\Neo4j\Index\NodeIndex,
		Everyman\Neo4j\Index\RelationshipIndex,
        Everyman\Neo4j\Relationship,
        Everyman\Neo4j\Node,
        Everyman\Neo4j\Cypher;

    if(isset($_POST['usuario'])){
    	$client = new Client();
		$run = "MATCH (p:Person) WHERE " .
				"p.usuario = '{$_POST['usuario']}' AND p.password = '" . md5($_POST['senha']) . "' " . 
				"return p.usuario";

		$query = new Cypher\Query($client, $run);
        $result = $query->getResultSet();
        foreach($result as $row) {
        	$usuario = $row->offsetGet('p.usuario');
	    }
	    if(isset($usuario)){
	    	$_SESSION['usuario'] = $usuario;
	    } else {
	    	echo "Login inválido!<br>";
	    }
    }
?>
<form method=POST>
	Usuário: <input type='text' name='usuario'><br>
	Senha: <input type='password' name='senha'><br>
	<input type='submit'>
</form>