<!-- Left side column. contains the logo and sidebar -->
<aside class="main-sidebar">

    <!-- sidebar: style can be found in sidebar.less -->
    <section class="sidebar">

        <!-- Sidebar user panel (optional) -->
        @if (! Auth::guest())
<!--             <div class="user-panel">
                <div class="pull-left image">
                    <img src="{{ Gravatar::get($user->email) }}" class="img-circle" alt="User Image" />
                </div>
                <div class="pull-left info"> -->
                    <!-- <p style="overflow: hidden;text-overflow: ellipsis;max-width: 160px;" data-toggle="tooltip" title="{{ Auth::user()->name }}">{{ Auth::user()->name }}</p> -->
                    <!-- Status -->
<!--                     <a href="#"><i class="fa fa-circle text-success"></i> {{ trans('adminlte_lang::message.online') }}</a>
                </div>
            </div> -->
        @endif

        <!-- search form (Optional) -->
<!--         <form action="#" method="get" class="sidebar-form">
            <div class="input-group">
                <input type="text" name="q" class="form-control" placeholder="{{ trans('adminlte_lang::message.search') }}..."/>
              <span class="input-group-btn">
                <button type='submit' name='search' id='search-btn' class="btn btn-flat"><i class="fa fa-search"></i></button>
              </span>
            </div>
        </form> -->
        <!-- /.search form -->

        <!-- Sidebar Menu -->
        <ul class="sidebar-menu" data-widget="tree">
        <!--     <li class="header">{{ trans('adminlte_lang::message.header') }}</li> -->
            <!-- Optionally, you can add icons to the links -->
<!--             <li class="active"><a href="{{ url('home') }}"><i class='fa fa-link'></i> <span>{{ trans('adminlte_lang::message.home') }}</span></a></li>
            <li><a href="#"><i class='fa fa-link'></i> <span>{{ trans('adminlte_lang::message.anotherlink') }}</span></a></li> -->
            <li class="treeview">
                <a href="#"><i class='fa fa-fighter-jet'></i> <span>{{ trans('adminlte_lang::message.uav') }}</span> <i class="fa fa-angle-left pull-right"></i></a>
                <ul class="treeview-menu">
                    <li><a href="/uavs/create">{{ trans('adminlte_lang::message.uav_insert') }}</a></li>
                    <li><a href="/uavs">{{ trans('adminlte_lang::message.uav_modify_delete') }}</a></li>
                </ul>
            </li>
            <li class="treeview">
                <a href="#"><i class='	fa fa-sitemap'></i> <span>{{ trans('adminlte_lang::message.device') }}</span> <i class="fa fa-angle-left pull-right"></i></a>
                <ul class="treeview-menu">
                <li><a href="/devices/create">{{ trans('adminlte_lang::message.device_insert') }}</a></li>
                    <li><a href="/devices">{{ trans('adminlte_lang::message.device_modify_delete') }}</a></li>
                </ul>
            </li>
            <li class="treeview">
                <a href="#"><i class='fa fa-link'></i> <span>{{ trans('adminlte_lang::message.network') }}</span> <i class="fa fa-angle-left pull-right"></i></a>
                <ul class="treeview-menu">
                <li><a href="/networks/create">{{ trans('adminlte_lang::message.network_insert') }}</a></li>
                    <li><a href="/networks">{{ trans('adminlte_lang::message.network_modify_delete') }}</a></li>
                </ul>
            </li>
            <li class="treeview">
                <a href="#"><i class='fa fa-cog'></i> <span>{{ trans('adminlte_lang::message.mpls_tag') }}</span> <i class="fa fa-angle-left pull-right"></i></a>
                <ul class="treeview-menu">
                <li><a href="/mpls_tags/create">{{ trans('adminlte_lang::message.mpls_tag_insert') }}</a></li>
                    <li><a href="/mpls_tags">{{ trans('adminlte_lang::message.mpls_tag_modify_delete') }}</a></li>
                </ul>
            </li>
            <li class="treeview">
                <a href="#"><i class='fa fa-road'></i> <span>{{ trans('adminlte_lang::message.route') }}</span> <i class="fa fa-angle-left pull-right"></i></a>
                <ul class="treeview-menu">
                <li><a href="/routes/create">{{ trans('adminlte_lang::message.route_insert') }}</a></li>
                    <li><a href="/routes">{{ trans('adminlte_lang::message.route_modify_delete') }}</a></li>
                </ul>
            </li>
        </ul><!-- /.sidebar-menu -->
    </section>
    <!-- /.sidebar -->
</aside>
