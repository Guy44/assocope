<?php
/*
 * <atom:feed xmlns:atom="http://www.w3.org/2005/Atom">
  <atom:author>
    <atom:name>John Doe</atom:name>
    <atom:email>user@gmail.com</atom:email>
  </atom:author>
  <atom:category term="http://schemas.google.com/contact/2008#contact" 
   scheme="http://schemas.google.com/g/2005#kind"/>
  <atom:id>user@gmail.com</atom:id>
  <atom:link href="http://www.google.com/" rel="alternate" type="text/html"/>
  <atom:link href="http://www.google.com/m8/feeds/contacts/user%40gmail.com/full" 
   rel="http://schemas.google.com/g/2005#feed" type="application/atom+xml"/>
  <atom:link href="http://www.google.com/m8/feeds/contacts/user%40gmail.com/full" 
   rel="http://schemas.google.com/g/2005#post" type="application/atom+xml"/>
  <atom:link href="http://www.google.com/m8/feeds/contacts/user%40gmail.com/full/
   batch" rel="http://schemas.google.com/g/2005#batch" type="application/atom+xml"/>
  <atom:link href="http://www.google.com/m8/feeds/contacts/user%40gmail.com/full?
   max-results=25" rel="self" type="application/atom+xml"/>
  <atom:link href="http://www.google.com/m8/feeds/contacts/user%40gmail.com/full?
   start-index=26&max-results=25" rel="next" type="application/atom+xml"/>
  <atom:title type="text">John Doe's Contacts</atom:title>
  <atom:updated>2009-08-31T10:48:00.410Z</atom:updated>
  <atom:generator uri="http://www.google.com/m8/feeds" version="1.0">Contacts
  </atom:generator>
  <atom:entry xmlns:default="http://www.w3.org/2007/app" 
   xmlns:default1="http://schemas.google.com/g/2005" 
   xmlns:default2="http://schemas.google.com/contact/2008">
    <default:edited xmlns="http://www.w3.org/2007/app">2009-08-22T16:52:37.457Z
    </default:edited>
    <default1:name xmlns="http://schemas.google.com/g/2005">
      <default1:fullName>Vikram Vaswani</default1:fullName>
      <default1:givenName>Vikram</default1:givenName>
      <default1:familyName>Vaswani</default1:familyName>
    </default1:name>
    <default1:organization xmlns="http://schemas.google.com/g/2005" 
     rel="http://schemas.google.com/g/2005#work">
      <default1:orgName>Melonfire</default1:orgName>
      <default1:orgTitle>CEO</default1:orgTitle>
    </default1:organization>
    <default1:email xmlns="http://schemas.google.com/g/2005" 
     rel="http://schemas.google.com/g/2005#other" address="vikram@example.org" 
     primary="true"/>
    <default1:email xmlns="http://schemas.google.com/g/2005" 
     rel="http://schemas.google.com/g/2005#home" address="vikram@example.com"/>
    <default1:phoneNumber xmlns="http://schemas.google.com/g/2005" 
     rel="http://schemas.google.com/g/2005#mobile">0012345678901
     </default1:phoneNumber>
    <default1:phoneNumber xmlns="http://schemas.google.com/g/2005" 
     rel="http://schemas.google.com/g/2005#work_fax">0045678901234
     </default1:phoneNumber>
    <default2:website xmlns="http://schemas.google.com/contact/2008" 
     href="http://www.melonfire.com/" rel="home"/>
    <default2:website xmlns="http://schemas.google.com/contact/2008" 
     href="http://www.php-beginners-guide.com/" rel="blog"/>
    <default2:groupMembershipInfo xmlns="http://schemas.google.com/contact/2008" 
     deleted="false" 
     href="http://www.google.com/m8/feeds/groups/user%40gmail.com/base/6"/>
    <atom:category term="http://schemas.google.com/contact/2008#contact" 
     scheme="http://schemas.google.com/g/2005#kind"/>
    <atom:id>http://www.google.com/m8/feeds/contacts/user%40gmail.com/base/0
    </atom:id>
    <atom:link href="http://www.google.com/m8/feeds/photos/media/user%40gmail.com/0" 
     rel="http://schemas.google.com/contacts/2008/rel#photo" type="image/*"/>
    <atom:link href="http://www.google.com/m8/feeds/contacts/user%40gmail.com/full/0" 
     rel="self" type="application/atom+xml"/>
    <atom:link href="http://www.google.com/m8/feeds/contacts/user%40gmail.com/full/0" 
     rel="edit" type="application/atom+xml"/>
    <atom:title type="text">Vikram Vaswani</atom:title>
    <atom:updated>2009-08-22T16:52:37.457Z</atom:updated>
    <atom:content type="text">PHP enthusiast</atom:content>
  </atom:entry>
  <atom:entry xmlns:default="http://www.w3.org/2007/app" 
   xmlns:default1="http://schemas.google.com/g/2005">
  </atom:entry>
  <openSearch:totalResults xmlns:openSearch="http://a9.com/-/spec/opensearchrss/1.0/"
  >153</openSearch:totalResults>
  <openSearch:startIndex xmlns:openSearch="http://a9.com/-/spec/opensearchrss/1.0/"
  >1</openSearch:startIndex>
  <openSearch:itemsPerPage xmlns:openSearch="http://a9.com/-/spec/opensearchrss/1.0/"
  >25</openSearch:itemsPerPage>
</atom:feed>


https://code.google.com/intl/fr/apis/gdata/docs/2.0/elements.html#gdContactKind
 */
function get_contacts()
{		$path = '/home/wikiservas/wikistoma.org/association/modules/library';
		set_include_path(get_include_path() . PATH_SEPARATOR . $path);

		require_once 'Zend/Loader.php';
    Zend_Loader::loadClass('Zend_Gdata');
    Zend_Loader::loadClass('Zend_Gdata_ClientLogin');
    Zend_Loader::loadClass('Zend_Http_Client');
    Zend_Loader::loadClass('Zend_Gdata_Query');
    Zend_Loader::loadClass('Zend_Gdata_Feed');
    
    // set credentials for ClientLogin authentication
    $user = "";
    $pass = "";
    
    try {
      // perform login and set protocol version to 3.0
      $client = Zend_Gdata_ClientLogin::getHttpClient(
        $user, $pass, 'cp');
      $gdata = new Zend_Gdata($client);
      $gdata->setMajorProtocolVersion(3);
      
      // perform query and get result feed
      $query = new Zend_Gdata_Query(
        'http://www.google.com/m8/feeds/contacts/default/full');
      $feed = $gdata->getFeed($query);
      
      // display title and result count
      ?>
      
      <h2><?php echo $feed->title; ?></h2>
      <div>
      <?php echo $feed->totalResults; ?> contact(s) found.
      </div>
      
      <?php
      // parse feed and extract contact information
      // into simpler objects
      $results = array();
      foreach($feed as $entry){
        $xml = simplexml_load_string($entry->getXML());
        $obj = new stdClass;
        $obj->name = (string) $entry->title;
        $obj->orgName = (string) $xml->organization->orgName; 
        $obj->orgTitle = (string) $xml->organization->orgTitle; 
      
        foreach ($xml->email as $e) {
          $obj->emailAddress[] = (string) $e['address'];
        }
        
        foreach ($xml->phoneNumber as $p) {
          $obj->phoneNumber[] = (string) $p;
        }
        foreach ($xml->website as $w) {
          $obj->website[] = (string) $w['href'];
        }
        
        $results[] = $obj;  
      }
    } catch (Exception $e) {
      die('ERROR:' . $e->getMessage());  
    }
    ?>
    
    <?php
    // display results
    foreach ($results as $r) {
    ?>
    <div class="entry">
      <div class="name"><?php echo (!empty($r->name)) ? 
       $r->name : 'Name not available'; ?></div>
      <div class="data">
        <table>
          <tr>
            <td>Organization</td>
            <td><?php echo $r->orgName; ?></td>
          </tr>
          <tr>
            <td>Email</td>
            <td><?php echo @join(', ', $r->emailAddress); ?></td>
          </tr>
          <tr>
            <td>Phone</td>
            <td><?php echo @join(', ', $r->phoneNumber); ?></td>
          </tr>
          <tr>
            <td>Web</td>
            <td><?php echo @join(', ', $r->website); ?></td>
          </tr>
        </table>
      </div>
    </div>
    <?php
    }
}
    ?>
    
    
    <?php
    function add_contact()
    {
// load Zend Gdata libraries
require_once 'Zend/Loader.php';
Zend_Loader::loadClass('Zend_Gdata');
Zend_Loader::loadClass('Zend_Gdata_ClientLogin');
Zend_Loader::loadClass('Zend_Http_Client');
Zend_Loader::loadClass('Zend_Gdata_Query');
Zend_Loader::loadClass('Zend_Gdata_Feed');

// set credentials for ClientLogin authentication
$user = "user@gmail.com";
$pass = "guessme";

try {
  // perform login and set protocol version to 3.0
  $client = Zend_Gdata_ClientLogin::getHttpClient(
    $user, $pass, 'cp');
  $gdata = new Zend_Gdata($client);
  $gdata->setMajorProtocolVersion(3);
  
  // create new entry
  $doc  = new DOMDocument();
  $doc->formatOutput = true;
  $entry = $doc->createElement('atom:entry');
  $entry->setAttributeNS('http://www.w3.org/2000/xmlns/' ,
   'xmlns:atom', 'http://www.w3.org/2005/Atom');
  $entry->setAttributeNS('http://www.w3.org/2000/xmlns/' ,
   'xmlns:gd', 'http://schemas.google.com/g/2005');
  $doc->appendChild($entry);
  
  // add name element
  $name = $doc->createElement('gd:name');
  $entry->appendChild($name);
  $fullName = $doc->createElement('gd:fullName', 'Jack Frost');
  $name->appendChild($fullName);
  
  // add email element
  $email = $doc->createElement('gd:email');
  $email->setAttribute('address' ,'jack.frost@example.com');
  $email->setAttribute('rel' ,'http://schemas.google.com/g/2005#home');
  $entry->appendChild($email);
  
  // add org name element
  $org = $doc->createElement('gd:organization');
  $org->setAttribute('rel' ,'http://schemas.google.com/g/2005#work');
  $entry->appendChild($org);
  $orgName = $doc->createElement('gd:orgName', 'Winter Inc.');
  $org->appendChild($orgName);
  
  // insert entry
  $entryResult = $gdata->insertEntry($doc->saveXML(), 
   'http://www.google.com/m8/feeds/contacts/default/full');
  echo '<h2>Add Contact</h2>';
  echo 'The ID of the new entry is: ' . $entryResult->id;
} catch (Exception $e) {
  die('ERROR:' . $e->getMessage());
}
    }
    function delete_contact()
    {
    // load Zend Gdata libraries
require_once 'Zend/Loader.php';
Zend_Loader::loadClass('Zend_Gdata');
Zend_Loader::loadClass('Zend_Gdata_ClientLogin');
Zend_Loader::loadClass('Zend_Http_Client');
Zend_Loader::loadClass('Zend_Gdata_Query');
Zend_Loader::loadClass('Zend_Gdata_Feed');

// set credentials for ClientLogin authentication
$user = "user@gmail.com";
$pass = "guessme";

// set ID of entry to delete
// from <link rel=edit>
$id = 'http://www.google.com/m8/feeds/contacts/default/base/29e98jf648c495c7b';

try {
  // perform login and set protocol version to 3.0
  $client = Zend_Gdata_ClientLogin::getHttpClient(
    $user, $pass, 'cp');
  $client->setHeaders('If-Match: *');
  $gdata = new Zend_Gdata($client);
  $gdata->setMajorProtocolVersion(3);
  
  // delete entry
  $gdata->delete($id);
  echo '<h2>Delete Contact</h2>';
  echo 'Entry deleted';
} catch (Exception $e) {
  die('ERROR:' . $e->getMessage());
}
    }
    function modify_contact()
    {
    // load Zend Gdata libraries
require_once 'Zend/Loader.php';
Zend_Loader::loadClass('Zend_Gdata');
Zend_Loader::loadClass('Zend_Gdata_ClientLogin');
Zend_Loader::loadClass('Zend_Http_Client');
Zend_Loader::loadClass('Zend_Gdata_Query');
Zend_Loader::loadClass('Zend_Gdata_Feed');

// set credentials for ClientLogin authentication
$user = "user@gmail.com";
$pass = "guessme";

// set ID of entry to update
// from <link rel=self>
$id = 'http://www.google.com/m8/feeds/contacts/default/full/0';

try {
  // perform login and set protocol version to 3.0
  $client = Zend_Gdata_ClientLogin::getHttpClient(
    $user, $pass, 'cp');
  $client->setHeaders('If-Match: *');

  $gdata = new Zend_Gdata($client);
  $gdata->setMajorProtocolVersion(3);
  
  // perform query and get entry
  $query = new Zend_Gdata_Query($id);
  $entry = $gdata->getEntry($query);
  $xml = simplexml_load_string($entry->getXML());

  // change name
  $xml->name->fullName = 'John Rabbit';
  
  // change primary email address  
  foreach ($xml->email as $email) {
    if (isset($email['primary'])) {
      $email['address'] = 'jr@example.com';  
    }  
  }
  
  // update entry
  $entryResult = $gdata->updateEntry($xml->saveXML(), 
   $entry->getEditLink()->href);
  echo 'Entry updated';
} catch (Exception $e) {
  die('ERROR:' . $e->getMessage());
}
    }
 /*
The start-index parameter specifies the start offset for the feed
The max-results parameter specifies the number of entries in the feed
The orderby and sortorder parameters specify how to sort feed entries
The showdeleted parameter includes entries deleted in the last 30 days in the feed
  */   
    function additional_parameters ()
    {
    // load Zend Gdata libraries
require_once 'Zend/Loader.php';
Zend_Loader::loadClass('Zend_Gdata');
Zend_Loader::loadClass('Zend_Gdata_ClientLogin');
Zend_Loader::loadClass('Zend_Http_Client');
Zend_Loader::loadClass('Zend_Gdata_Query');
Zend_Loader::loadClass('Zend_Gdata_Feed');

// set credentials for ClientLogin authentication
$user = "user@gmail.com";
$pass = "guessme";

try {
  // perform login and set protocol version to 3.0
  $client = Zend_Gdata_ClientLogin::getHttpClient(
    $user, $pass, 'cp');
  $gdata = new Zend_Gdata($client);
  $gdata->setMajorProtocolVersion(3);
  
  // perform query and get result feed
  $query = new Zend_Gdata_Query(
    'http://www.google.com/m8/feeds/contacts/default/full');
  $query->maxResults = 10;
  $query->setParam('orderby', 'lastmodified');
  $query->setParam('sortorder', 'descending');
  $feed = $gdata->getFeed($query);

  // display title and result count
  // snip...
} catch (Exception $e) {
  die('ERROR:' . $e->getMessage());  
}
    }
?>

