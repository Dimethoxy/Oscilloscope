%global git_hash %{?git_hash}

Name:           dimethoxy-oscilloscope-snapshot
Version:        0.1
Release:        %{?git_hash}.1%{?dist}
Summary:        Unstable build of the latest commit of Oscilloscope from Dimethoxy's GitHub repository
License:        GPL-3.0-or-later
URL:            https://github.com/Dimethoxy/Oscilloscope
Source0:        dimethoxy-oscilloscope-snapshot-%{git_hash}.tar.gz
Conflicts:      dimethoxy-oscilloscope
Requires:       curl

%description
Unstable build of the latest commit of Oscilloscope from Dimethoxy's GitHub repository.

%prep
# Extract the tarball containing the pre-built artifacts
%setup -q

%install
# Create the base installation directories
install -d %{buildroot}/usr/lib/vst3
install -d %{buildroot}/usr/lib/lv2
install -d %{buildroot}/usr/lib/clap
install -d %{buildroot}/usr/share/licenses/%{name}

# Copy the plugin format directories directly from the extracted source directory
cp -r oscilloscope-snapshot-linux-fedora/VST3/* %{buildroot}/usr/lib/vst3/
cp -r oscilloscope-snapshot-linux-fedora/LV2/* %{buildroot}/usr/lib/lv2/
cp -r oscilloscope-snapshot-linux-fedora/CLAP/* %{buildroot}/usr/lib/clap/

# Install the license file
if [ -f "LICENSE" ]; then
    install -Dm644 LICENSE %{buildroot}/usr/share/licenses/%{name}/LICENSE
else
    curl -L "https://raw.githubusercontent.com/Dimethoxy/Oscilloscope/main/LICENSE" -o %{buildroot}/usr/share/licenses/%{name}/LICENSE
fi

%files
/usr/lib/vst3/Oscilloscope
/usr/lib/lv2/Oscilloscope
/usr/lib/clap/Oscilloscope
/usr/share/licenses/%{name}/LICENSE
