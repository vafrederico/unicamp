<?php 
	if(!isset($_SESSION)){
		session_start();
	}
	if(!(isset($_SESSION['usuario']) && $_SESSION['usuario'] != -1))
		header('Location: login.php');

	require("phar://neo4jphp.phar");
	use Everyman\Neo4j\Client,
        Everyman\Neo4j\Index\NodeIndex,
		Everyman\Neo4j\Index\RelationshipIndex,
        Everyman\Neo4j\Relationship,
        Everyman\Neo4j\Node,
        Everyman\Neo4j\Cypher;
	if(isset($_POST['uri'])){
		$client = new Client();
		$run = "" .
"MERGE (a:Artista {uri: '{$_POST['uri']}'}) " .
"ON CREATE a SET a.uri='{$_POST['uri']}' " .
"ON MATCH a SET a.existed=1 " .
"RETURN a.existed; ";
		$query = new Cypher\Query($client, $run);
        $result = $query->getResultSet();
 foreach($result as $row) {
        	$existed = ($row->offsetGet('a.existed')?true:0);
        }
        if(!$existed){
			$run = "" . 
	"MATCH (n:Person), (m:Artista) " .
	"WHERE n.usuario='{$_SESSION['usuario']}' " .
	"AND m.uri='{$_POST['uri']}' " .
	"CREATE UNIQUE n-[:LIKES{rating: {$_POST['rating']}}]->m " .
	"return n, m";
			$query = new Cypher\Query($client, $run);
	        $result = $query->getResultSet();
	        header('Location: artistas.php');
    	} else {
    		echo "Artista já existente";
    	}
	}
?>
<form method="POST">
	URI: <input type='text' name='uri'><br>
	Nota: <select name='rating'>
	<option value='1'>1</option>
	<option value='2'>2</option>
	<option value='3'>3</option>
	<option value='4'>4</option>
	<option value='5'>5</option>
</select>
	<br>
	<input type='submit'>
</form>