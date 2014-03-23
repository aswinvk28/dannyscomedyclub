<div id="page" class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <!-- ______________________ HEADER _______________________ -->
  
    <header class="header row-fluid">
        <div class="container mast-head">
            <div class="clearfix">
                <div class="span4 logo-container">
                    <h1 class="element-absent" itemprop="sourceOrganization"><?php print $site_name; ?></h1>
                    <div itemscope itemtype="http://schema.org/ComedyClub">
                    <?php if ($logo): ?>
                        <span itemprop="logo" itemscope itemtype="http://schema.org/ImageObject"><a itemprop="discussionUrl" href="<?php print $front_page; ?>">
                            <img itemprop="contentUrl" src="<?php print $logo; ?>" alt="<?php print $site_name; ?> Logo" title="<?php print $site_name; ?> Logo" />
                        </a></span>
                    <?php else: ?>
                    <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
                        <span itemprop="legalName"><?php print $site_name; ?></span>
                    </a>
                    <?php endif; ?>
                    <?php if( !empty($site_slogan) ): ?>
                        <h3 class="site-tagline"><?php print $site_slogan; ?></h3>
                    <?php endif; ?>
                    </div>
                </div>
                
                <div class="span4 white" itemscope itemtype="http://schema.org/ComedyClub">
                    <?php if( !empty($header_sidebar) ): ?>
                    <aside class="address-container clearfix column_small">
                        <?php print $header_sidebar; ?>
                    </aside>
                    <?php endif; ?>
                </div>
                
                <div class="span4 white">
                    <?php if( !empty($follow_us) ): ?>
                    <aside class="social-networking-following clearfix column_small">
                        <?php print $follow_us; ?>
                    </aside>
                    <?php endif; ?>
                    
                    <?php if( !empty($share_on) ): ?>
                    <aside class="social-networking-sharing clearfix column_small">
                        <?php print $share_on; ?>
                    </aside>
                    <?php endif; ?>
                </div>
            </div>
            
            <?php if ($main_menu): ?>
            <div class="navigation border_radius" itemscope itemtype="http://schema.org/SiteNavigationElement">
                <?php print theme('links', array('links' => $main_menu, 'attributes' => array('id' => 'main-menu', 'class' => array('nav', 'nav-pills')))); ?>
            </div>
            <?php endif; ?>
        </div>
    </header>

  <!-- ______________________ MAIN _______________________ -->

  <section class="page_holder container">
      <?php if ($breadcrumb || $title|| $messages || $tabs || $action_links): ?>
        <div id="content-header">

          <?php if ($page['highlight']): ?>
            <div id="highlight"><?php print render($page['highlight']) ?></div>
          <?php endif; ?>

          <?php if ($title): ?>
            <hgroup class="column_title">
                <h1><?php print $title; ?></h1>
            </hgroup>
          <?php endif; ?>

          <?php if($is_admin) { print $messages; } ?>
          <?php print render($page['help']); ?>

          <?php if ($tabs): ?>
            <div class="tabs"><?php print render($tabs); ?></div>
          <?php endif; ?>

          <?php if ($action_links): ?>
            <ul class="action-links"><?php print render($action_links); ?></ul>
          <?php endif; ?>
          
        </div>
      <?php endif; ?>

  	<div class="clearfix decolumn_mini">  
          <div class="alert alert-info">
              <p><?php print drupal_render($page['notice']); ?></p>
          </div>
          <div class="row-fluid">
              <div id="main" class="<?php echo $content_classes; ?>">
                <?php print $accordion; ?>
              </div>
              <?php if(!empty($page['sidebar'])):
                echo drupal_render($page['sidebar']);
              endif; ?>
	  </div>
	</div>
      
    <div class="column clearfix">
      <div class="row-fluid">
          <div itemprop="mainContentOfPage" itemscope itemtype="http://schema.org/WebPageElement">
            <?php print drupal_render( $page['information'] );
            print drupal_render( $page['content'] ); ?>
          </div>
      </div>
    </div>
	
  </section>

  <!-- ______________________ FOOTER _______________________ -->

 <footer class="footer" itemscope itemtype="http://schema.org/WPFooter">
    <div class="container">
        <?php if($secondary_menu): ?>
        <div class="clearfix" itemscope itemtype="http://schema.org/SiteNavigationElement">
            <?php print theme('links', array('links' => $secondary_menu, 'attributes' => array('id' => 'secondary-menu', 'class' => array('align-center', 'unstyled')))); ?>
        </div>
        <?php endif; ?>
        <div class="row-fluid">
            <p class="span6">
                <?php 
                print t('Copyright &copy; ') .'<span itemprop="copyrightYear">' . t('@date', array('@date' => date('Y'))) . ' </span>' . 
                '<span itemprop="copyrightHolder" itemscope itemtype="http://schema.org/ComedyClub"><span itemprop="legalName">' . 
                t('@site_name', array('@site_name' => $site_name)) . '</span></span>'; ?>
            </p>
            <p class="span6 align-right">
                Website Designed by <span itemprop="editor">Aswin Vijayakumar</span>
            </p>
        </div>
    </div>
</footer>

</div>