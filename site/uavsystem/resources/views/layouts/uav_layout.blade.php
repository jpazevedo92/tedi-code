@extends('adminlte::layouts.app')

@section('main-content')
	<div class="container-fluid spark-screen">
		<div class="row">
			<div class="col-md-8 col-md-offset-2">

            <form class="form-horizontal" action="{{isset($uav) ? '/uavs/'.$uav->id : '/uavs'}}" method="POST" enctype = "multipart/form-data" id="uav">
            {{ isset($uav) ? method_field('PATCH') : ''}}
            {{ csrf_field() }}
                <!-- Default box -->
				<div class="box">
					<div class="box-header with-border">
						<h3 class="box-title">@yield('uav_box_title')</h3>
						<div class="box-tools pull-right">
							<button type="button" class="btn btn-box-tool" data-widget="collapse" data-toggle="tooltip" title="Collapse">
								<i class="fa fa-minus"></i></button>
						</div>
					</div>
					<div class="box-body">
                        @yield('uav_main_content')
					</div>
					<!-- /.box-body -->
				</div>
				<!-- /.box -->
                <!-- Default box -->
				<div class="box">
					<div class="box-header with-border">
						<h3 class="box-title">@yield('network_box_title')</h3>
						<div class="box-tools pull-right">
							<button type="button" class="btn btn-box-tool" data-widget="collapse" data-toggle="tooltip" title="Collapse">
								<i class="fa fa-minus"></i></button>
						</div>
					</div>
					<div class="box-body">
                        @yield('uav_network_content')
					</div>
					<!-- /.box-body -->
				</div>
				<!-- /.box -->
                <div class="form-group">
                <div class="col-sm-offset-2 col-sm-10">
                    <button type="submit" class="btn btn-default">{{ isset($uav) ?  'Update' : 'Submit' }}</button>
                </div>
            </div> 
            </form>

			</div>
		</div>
	</div>
@endsection
